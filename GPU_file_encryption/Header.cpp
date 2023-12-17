#include "Header.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

AEScipher::AEScipher(std::string pathkey, std::string folder)
{
    std::vector<char> keyforcopy;
    keyforcopy = ReadFile(pathkey);

    std::vector<unsigned char> currentLine;

    for (char ch : keyforcopy) {
        if (ch == '\n') {
            // Если встречен символ новой строки, добавляем текущую строку в data
            keyss.push_back(currentLine);
            currentLine.clear(); 
        }
        else {
            // Добавляем символ в текущую строку
            currentLine.push_back(static_cast<unsigned char>(ch));
        }
    }

    // Добавляем последнюю строку, если она не заканчивается символом новой строки
    if (!currentLine.empty()) {
        keyss.push_back(currentLine) ;
    }


    std::vector<char> filestr;


    std::vector<unsigned char> currentLineFile;


    for (const auto& entry : fs::directory_iterator(folder)) {


        std::string filename = entry.path().generic_string();
        std::vector<char> fileContent = ReadFile(filename);

        if (!fileContent.empty()) {

            std::vector<unsigned char> unsignedFileContent(fileContent.begin(), fileContent.end());

            files.push_back(std::move(unsignedFileContent));
        }
    }        
}

void AEScipher::WriteFile(std::vector<unsigned char > writedata, const std::string path)
{
    std::ofstream outFile(path, std::ios::binary);

    if (!outFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
    }

    outFile.write(reinterpret_cast<const char*>(writedata.data()), writedata.size());

    outFile.close();
}

std::vector<char> AEScipher::ReadFile(std::string path) {
    std::ifstream inputFile(path, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return std::vector<char>();
    }

    std::vector<char> buffer(64);
    inputFile.read(buffer.data(), buffer.size());

    inputFile.close();

    return buffer;
}

// Ôóíêöèÿ äëÿ âûâîäà ìàññèâà
void AEScipher::printArray(unsigned char* arr, int length) {
    for (int i = 0; i < length; ++i) {
        std::cout << std::hex << (int)arr[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

// Ôóíêöèÿ äëÿ ðàñøèðåíèÿ êëþ÷à
void AEScipher::keyExpansion(unsigned char* key, unsigned char w[][4][4]) {
    int i, j, r, c;
    unsigned char rc[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

    for (r = 0; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            w[0][r][c] = key[r + c * 4];
        }
    }


    for (i = 1; i <= 10; ++i) {
        for (j = 0; j < 4; ++j) {
            unsigned char t[4];
            for (r = 0; r < 4; ++r) {
                t[r] = (j == 0) ? w[i - 1][r][3] : w[i][r][j - 1];
            }

            if (j == 0) {
                unsigned char temp = t[0];
                for (r = 0; r < 3; ++r) {
                    t[r] = w[i][r][(r + 1) % 4];
                }
                t[3] = temp;
                t[0] ^= rc[i - 1];
            }

            for (r = 0; r < 4; ++r) {
                w[i][r][j] = w[i - 1][r][j] ^ t[r];
            }
        }
    }
}

// Ôóíêöèÿ äëÿ âûïîëíåíèÿ îïåðàöèè FFmul
unsigned char AEScipher::ffMultiply(unsigned char a, unsigned char b) {
    unsigned char bw[4];
    unsigned char res = 0;
    int i;

    bw[0] = b;
    for (i = 1; i < 4; ++i) {
        bw[i] = bw[i - 1] << 1;
        if (bw[i - 1] & 0x80) {
            bw[i] ^= 0x1b;
        }
    }

    for (i = 0; i < 4; ++i) {
        if ((a >> i) & 0x01) {
            res ^= bw[i];
        }
    }

    return res;
}

// Ôóíêöèÿ äëÿ çàìåíû áàéòîâ â ìàòðèöå ñîñòîÿíèÿ
void AEScipher::subBytes(unsigned char state[][4], const unsigned char* sBox) {
    int r, c;
    for (r = 0; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            state[r][c] = sBox[state[r][c]];
        }
    }
}

// Ôóíêöèÿ äëÿ öèêëè÷åñêîãî ñäâèãà ñòðîê â ìàòðèöå ñîñòîÿíèÿ
void AEScipher::shiftRows(unsigned char state[][4]) {
    unsigned char t[4];
    int r, c;
    for (r = 1; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            t[c] = state[r][(c + r) % 4];
        }
        for (c = 0; c < 4; ++c) {
            state[r][c] = t[c];
        }
    }
}

// Ôóíêöèÿ äëÿ ÎÁÐÀÒÍÎÃÎ öèêëè÷åñêîãî ñäâèãà ñòðîê â ìàòðèöå ñîñòîÿíèÿ
void AEScipher::InvShiftRows(unsigned char state[][4]) {
    unsigned char t[4];
    int r, c;
    for (r = 1; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            t[(c + r) % 4] = state[r][c];
        }
        for (c = 0; c < 4; ++c) {
            state[r][c] = t[c];
        }
    }
}

// Ôóíêöèÿ äëÿ ïåðåìåøèâàíèÿ ñòîëáöîâ â ìàòðèöå ñîñòîÿíèÿ
void AEScipher::mixColumns(unsigned char state[][4]) {
    unsigned char t[4];
    int r, c;
    for (c = 0; c < 4; ++c) {
        for (r = 0; r < 4; ++r) {
            t[r] = state[r][c];
        }
        for (r = 0; r < 4; ++r) {
            state[r][c] = ffMultiply(0x02, t[r]) ^
                ffMultiply(0x03, t[(r + 1) % 4]) ^
                ffMultiply(0x01, t[(r + 2) % 4]) ^
                ffMultiply(0x01, t[(r + 3) % 4]);
        }
    }
}

// Ôóíêöèÿ äëÿ ÎÁÐÀÒÍÎÃÎ ïåðåìåøèâàíèÿ ñòîëáöîâ â ìàòðèöå ñîñòîÿíèÿ
void AEScipher::InvMixColumns(unsigned char state[][4]) {
    unsigned char t[4];
    int r, c;
    for (c = 0; c < 4; ++c) {
        for (r = 0; r < 4; ++r) {
            t[r] = state[r][c];
        }
        for (r = 0; r < 4; ++r) {
            state[r][c] = ffMultiply(0x0E, t[r]) ^
                ffMultiply(0x0B, t[(r + 1) % 4]) ^
                ffMultiply(0x0D, t[(r + 2) % 4]) ^
                ffMultiply(0x09, t[(r + 3) % 4]);
        }
    }
}

// Ôóíêöèÿ äëÿ âûïîëíåíèÿ îïåðàöèè XOR íàä ìàòðèöàìè ñîñòîÿíèÿ è êëþ÷à ðàóíäà
void AEScipher::addRoundKey(unsigned char state[][4], unsigned char k[][4]) {
    int r, c;
    for (c = 0; c < 4; ++c) {
        for (r = 0; r < 4; ++r) {
            state[r][c] ^= k[r][c];
        }
    }
}

// Ôóíêöèÿ äëÿ øèôðîâàíèÿ áëîêà äàííûõ
void AEScipher::cipher(unsigned char* input, unsigned char w[][4][4], const unsigned char* sBox) {
    unsigned char state[4][4];
    int i, r, c;

    for (r = 0; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            state[r][c] = input[c * 4 + r];
        }
    }

    addRoundKey(state, w[0]);

    for (i = 1; i <= 10; ++i) {
        subBytes(state, sBox);
        shiftRows(state);
        if (i != 10) mixColumns(state);
        addRoundKey(state, w[i]);
    }

    for (r = 0; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            input[c * 4 + r] = state[r][c];
        }
    }
}

// Ôóíêöèÿ äëÿ èíâåðòèðîâàíèÿ SBox
void invertSBox(const unsigned char* sBox, unsigned char* invSBox) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            invSBox[sBox[i * 16 + j]] = static_cast<unsigned char>(i * 16 + j);
        }
    }
}

// Ôóíêöèÿ äëÿ äåøèôðîâàíèÿ áëîêà äàííûõ
void AEScipher::InvCipher(unsigned char* input, unsigned char w[][4][4], const unsigned char* invSBox) {
    unsigned char state[4][4];
    int i, r, c;

    for (r = 0; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            state[r][c] = input[c * 4 + r];
        }
    }

    addRoundKey(state, w[10]);

    for (i = 9; i >= 0; --i) {
        InvShiftRows(state);
        subBytes(state, invSBox);
        addRoundKey(state, w[i]);
        if (i != 0) InvMixColumns(state);
    }

    for (r = 0; r < 4; ++r) {
        for (c = 0; c < 4; ++c) {
            input[c * 4 + r] = state[r][c];
        }
    }
}

//unsigned char* AEScipher::EncryptionAES()
//{
//    if (keyss.empty() || files.empty()) {
//        std::cerr << "Key or file data is missing." << std::endl;
//        return nullptr;
//    }
//
//    // Итерация по всем элементам files
//    for (size_t i = 0; i < files.size(); ++i) {
//        // Замена file на files[i].data()
//        unsigned char* file = files[i].data();
//
//        unsigned char iSBox[256];
//        invertSBox(sBox, iSBox);
//
//        for (size_t j = 0; j < keyss.size(); ++j) {
//            unsigned char* key = keyss[j].data();
//            keyExpansion(key, w);
//            for (size_t j = 0; j < 4; ++j) {
//                unsigned char* block = file + j * 16;
//                cipher(block, w, sBox);
//            }
//        }
//
//
//    }
//
//    return files[0].data();
//}

unsigned char* AEScipher::EncryptionAES(unsigned char* fileEn, unsigned char* keyEn)
{

    unsigned char* output;
    unsigned char iSBox[256];

    invertSBox(sBox, iSBox);
    keyExpansion(keyEn, w);

    for (size_t i = 0; i < 4; ++i) {
        unsigned char* block = fileEn + i * 16;
        cipher(block, w, sBox);
    }

    return fileEn;

}



unsigned char* AEScipher::DecryptionAES(unsigned char* fileEn)
{
    if (keyss.empty() || files.empty()) {
        std::cerr << "Key or file data is missing." << std::endl;
        return nullptr;
    }

    unsigned char iSBox[256];
    invertSBox(sBox, iSBox);

    for (size_t i = 0; i < 4; ++i) {
        unsigned char* block = fileEn + i * 16;
        InvCipher(block, w, iSBox);
    }

    return fileEn;
}
