#include "rsa.h"

rsa::rsa()
{
    folder_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); // Standard Andriod phone path
    create_file(file_path_name);
    generate_private_key();
    generate_public_key();
    encrypt_data();

}
// ENCRYPTION PART IS NOT DONE AND COMPLETE. I CAN ONLY GENERATE KEYS
void rsa::generate_private_key()
{
    const int kBits = 1024;
    const int kExp = 65537; // could be whaterver as long as the exponent is a odd number, should be changed frequently because of security

    int keylen_private;

    private_rsa = RSA_generate_key(kBits, kExp, 0, 0);

    bioPv = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPrivateKey(bioPv, private_rsa, NULL, NULL, 0, NULL, NULL);

    keylen_private = BIO_pending(bioPv);

    private_key = static_cast<char*>(calloc(keylen_private+1,1));

    BIO_read(bioPv, private_key, keylen_private);

    qDebug() << private_key;
    write_to_phone_file(private_key);
}




void rsa::encrypt_data()
{
    BIO* bo = BIO_new(BIO_s_mem());

    BIO_write(bo, public_key, strlen(public_key));
    PEM_write_bio_RSAPublicKey(bo, public_rsa);
    PEM_read_bio_RSAPublicKey(bo, &public_rsa, 0, 0);
    BIO_free(bo);
    qDebug() << public_rsa;
    char *encrypt = NULL;
    encrypt = (char*)malloc(RSA_size(public_rsa));
    //public_encrypt(strlen(msg), (unsigned char*)msg, (unsigned char*)encrypt,public_rsa , RSA_PKCS1_OAEP_PADDING);

    RSA_free(public_rsa);
    free(encrypt);


}


void rsa::generate_public_key()
{
    const int kBits = 1024;
    const int kExp = 65537; // could be whaterver as long as the exponent is a odd number, should be changed frequently because of security
    int keylen_public;

    public_rsa = RSA_generate_key(kBits, kExp, 0, 0);
    bioPe = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPublicKey(bioPe, public_rsa);

    keylen_public = BIO_pending(bioPe);

    public_key = static_cast<char*>(calloc(keylen_public+1,1));

    BIO_read(bioPe, public_key, keylen_public);

    qDebug() << public_key;
}

void rsa::write_to_phone_file(std::string data)
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

void rsa::create_file(std::string file_name)
{
    file = new QFile(QString(folder_path + "/" + file_name.c_str()));
    if(QFile::exists(folder_path + "/" + file_path_name.c_str()))
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

rsa::~rsa()
{
    free(private_key);

    BIO_free_all(bioPv);



    BIO_free_all(bioPe);

    RSA_free(public_rsa);
    RSA_free(private_rsa);
    free(public_key);
    file->close();

    delete file;
}
