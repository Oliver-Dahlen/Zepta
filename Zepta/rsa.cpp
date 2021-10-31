#include "rsa.h"
#include <fstream>

#define KEY_LENGTH  2048
#define PUB_EXP     3

rsa::rsa()
{
    OpenSSL_add_all_algorithms(); // This should be pre-loaded but just in case.
    folder_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); // Standard Andriod phone path


    generate_private_key();
    generate_public_key();
    //auto data = encrypt_data(plainText);
    //qDebug() << decrypy_data(data);

}

void rsa::generate_private_key()
{
    // Generate the key
    signed int pri_len;

    key = RSA_generate_key(KEY_LENGTH, PUB_EXP, NULL, NULL);

    BIO *private_bio = BIO_new(BIO_s_mem());
    BIO_set_flags( private_bio, BIO_FLAGS_BASE64_NO_NL );
    PEM_write_bio_RSAPrivateKey(private_bio, key, NULL, NULL, 0, NULL, NULL);

    pri_len = BIO_pending(private_bio);

    private_key = (char*)malloc(pri_len + 1);

    BIO_read(private_bio, private_key, pri_len);

    private_key[pri_len] = '\0';

    //Write key to file, so it can be used multiple times

    create_file(private_key_path_name);
    write_to_phone_file(private_key, private_key_path_name);

    BIO_free_all(private_bio);
    //qDebug() << private_key;

}

void rsa::generate_public_key()
{
    signed int pub_len;

    BIO *pub = BIO_new(BIO_s_mem());
    BIO_set_flags( pub, BIO_FLAGS_BASE64_NO_NL );

    PEM_write_bio_RSAPublicKey(pub, key);

    pub_len = BIO_pending(pub);

    public_key = (char*)malloc(pub_len + 1);

    BIO_read(pub, public_key, pub_len);

    public_key[pub_len] = '\0';

    //Write key to file, so it can be used multiple times

    create_file(public_key_path_name);
    write_to_phone_file(public_key, public_key_path_name);

    BIO_free_all(pub);


}


RSA* rsa::get_public_key(std::string path)
{
    auto file = QFile(folder_path + "/" + path.c_str());
    file.open(QIODevice::ReadOnly);

    FILE *cFILE;
    cFILE = fdopen(file.handle(), "r");

    RSA *public_rsa = NULL;
    PEM_read_RSAPublicKey(cFILE, &public_rsa, 0, 0);

    fclose(cFILE);
    file.close();

    return public_rsa;
}

RSA* rsa::get_private_key(std::string path)
{

    auto file = QFile(folder_path + "/" + path.c_str());
    file.open(QIODevice::ReadOnly);

    FILE *cFILE;
    cFILE = fdopen(file.handle(), "r");

    RSA *private_rsa = NULL;
    PEM_read_RSAPrivateKey(cFILE, &private_rsa, 0, 0);

    fclose(cFILE);
    file.close();

    return private_rsa;
}

char* rsa::decrypy_data(char* data, std::string path)
{
    RSA* rsa = get_private_key(path);

    decrypt = (char*)malloc(RSA_size(rsa));
    int u =RSA_private_decrypt(RSA_size(rsa), (unsigned char*)data, (unsigned char*)decrypt, rsa, RSA_PKCS1_PADDING);
    if(u == -1){qDebug() << "Failed to decrypt";}

    return  decrypt;

}

char* rsa::encrypt_data(char *data, std::string path)
{
    RSA* t = get_public_key(path);
    encrypt = NULL;

    encrypt = (char*)malloc(RSA_size(t));
    int encrypt_len;

    encrypt_len = RSA_public_encrypt(strlen(data), (unsigned char*)data, (unsigned char*)encrypt, t, RSA_PKCS1_PADDING);
    if(encrypt_len ==-1){qDebug() << "Failed to encrypt";}
    return encrypt;
}



void rsa::write_to_phone_file(std::string data, std::string file_path_name)
{
    if(!QFile::exists(folder_path + "/" + file_path_name.c_str()))
    {
        qDebug() << "No file exsits so creating one and asigning key";
        create_file(file_path_name);
        file->open(QIODevice::WriteOnly);
        file->write(data.c_str());
        qDebug() << "Written to file";
    }

    file->close();
}

char* rsa::read_to_phone_file(std::string path)
{
    if(QFile::exists(path.c_str()))
    {
        auto file = QFile(path.c_str());
        file.open(QIODevice::ReadOnly);
        auto buffer = file.readAll();

        file.close();
        return buffer.data();
    }
    return nullptr;

}

void rsa::create_file(std::string file_name)
{
    file = new QFile(QString(folder_path + "/" + file_name.c_str()));

    if(QFile::exists(folder_path + "/" + file_name.c_str()))
        return;

    if (!file->exists()) {
        // create the folder
        QDir* dir = new QDir(folder_path);
        if (!dir->exists())
        {
            qDebug() << "There was no folder... So creating one";
            dir->mkpath(".");
        }
        qDebug() << "Creating file";
        delete dir;
    }


}

char* rsa::get_public_key_text()
{
    return read_to_phone_file(folder_path.toStdString() + "/" + public_key_path_name.c_str());;
}
rsa::~rsa()
{
    free(private_key);



    RSA_free(key);
    free(public_key);
    file->close();

    delete file;
    EVP_cleanup();
}
