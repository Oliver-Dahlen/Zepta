import shutil
import socket
import os
import base64
import time
import select
import sock as sock
import re
import binascii


socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.bind(("192.168.1.211", 65432))
socket.listen(1)
conn, addr = socket.accept()


print("not find")




def write_public_code_to_line(lineNum, key):

    key = key.replace("\n", "\\n")

    with open('messages.txt', 'r+') as f:  # r+ does the work of rw
        lines = f.readlines()
        for i, line in enumerate(lines):
            if line.startswith(str(lineNum)):

                lines[i] = lines[i].strip() + key + "\n"
        f.seek(0)
        for line in lines:
            f.write(line)

def find_encrypted_message(num):
    if not num: return
    with open("messages.txt") as myFile:
        print(num)
        lines = myFile.readlines()
        line = str(lines[num-1]).split(";")
        if line[1] == "\n": #this means nothing on line
            conn.sendall(bytes("No data".encode("utf-8")))
            public_key = conn.recv(2048)
            write_public_code_to_line(43634, public_key.decode("utf-8"))

            myFile.close()
            return
        buffer = line[1].replace("\\n", "\n") #need to convert from file formate, do this in python insted because in c++ it will just be waste of time
        buffer = buffer[:len(buffer)-1]
        conn.sendall(bytes(buffer.encode("utf-8")))
        c = conn.recv(2048) #get encrypted data
        print(c.decode("utf-8") + "efeefef")

        myFile.close()
    with open('messages.txt', 'r+') as f:  # r+ does the work of rw
        lines = f.readlines()
        for i, line in enumerate(lines):
            if line.startswith(str(43634)):
                if lines[i].strip()[len(lines[i].strip())-1] == "n":
                    lines[i] = lines[i].strip() + ";" + str(c.decode("utf-8")) + "\n"
                    print("uu")
                else:
                    print("yy")
                    conn.sendall(bytes("Encrypted message already exsist".encode("utf-8")))

                    get_encrypted_message(find_line_by_room_code(room_code))
                    return
        f.seek(0)
        for line in lines:
            f.write(line)

        f.close()

def find_line_by_room_code(room_code):

    room_code = str(room_code.decode("utf-8"))

    print(room_code)
    with open("messages.txt") as myFile:
        for num, line in enumerate(myFile, 1):
            if re.search(r"\b{}\b".format(room_code), line):

                myFile.close()
                return num
    print("do")
    conn.sendall(bytes("The room code given is not valid".encode("utf-8")))
    myFile.close()
    return 0

def get_encrypted_message(num):
    if not num: return
    with open("messages.txt") as myFile:
        lines = myFile.readlines()
        line = str(lines[num-1]).split(";")
        conn.sendall(bytes(line[2].encode("utf-8")))

while True:
    try:
        room_code = conn.recv(2048)

        line_num = find_line_by_room_code(room_code)
        find_encrypted_message(line_num)

        time.sleep(0.1)

    except select.error:
        print("No connection to client")
        socket.listen()
        conn, addr = socket.accept()
        print(f"{addr} connected")








