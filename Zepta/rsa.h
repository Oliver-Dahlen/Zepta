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

    char* encrypt_data(char* data, std::string path);
    char* decrypy_data(char* data, std::string path);
    std::string public_key_path_name = "public_key.txt";
    std::string private_key_path_name = "private_key.txt";
    char* read_to_phone_file(std::string path);
    RSA* get_public_key(std::string path);
    char* get_public_key_text();
    void create_file(std::string file_name);
    QFile* file;


private:

    QString folder_path;

    char* private_key;
    char* public_key;

    RSA *key;

    char *decrypt = NULL;
    char* encrypt = NULL;

    void generate_private_key();
    void generate_public_key();
    RSA * get_private_key(std::string path);

    void write_to_phone_file(std::string data, std::string file_path_name);

};

#endif // RSA_H
