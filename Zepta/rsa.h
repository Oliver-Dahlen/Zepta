#ifndef RSA_H
#define RSA_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <QDebug>
#include <QStandardPaths>
#include <QtGlobal>
#include <QFile>
#include <QDir>

class rsa
{
public:
    rsa();
    ~rsa();

    void write_to_phone_file(std::string data);
    char* read_to_phone_file();

    void generate_private_key();
    void generate_public_key();

    void encrypt_data();
    void decrypy_data();
     char * msg;
private:
    QFile* file;
    const std::string file_path_name = "private_key.txt";
    QString folder_path;

    char* private_key;
    char* public_key;

    RSA *private_rsa;
    RSA *public_rsa;

    BIO *bioPe;
    BIO *bioPv;
    void create_file(std::string file_name);
};

#endif // RSA_H
