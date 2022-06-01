// parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
using namespace std;
#include <iostream>

unsigned short Crc16(unsigned char* buf, unsigned short len) {
    unsigned short crc = 0xFFFF;
    unsigned char i;
    while (len--) {
        crc ^= *buf++ << 8;
        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}


float read_float(const char* data)
{
    float retval;
    float* rv_ptr = &retval;
    char* ptr = (char*)rv_ptr;
    memcpy(ptr, data, 4);
    return retval;
}



unsigned short pars_b(unsigned char* buf, size_t len, std::ofstream* fout)
{
    for (size_t i = 0; i < len; i++)
    {
        uint8_t buf_byte_pack1[32];
        uint8_t buf_byte_pack2[32];

        if (buf[i] = 0xff)
        {
            for (size_t j = 0; j < 32; j++) buf_byte_pack1[j] = buf[j];
            const uint16_t expected = ((uint16_t)buf_byte_pack1[31] << 8) | (buf_byte_pack1[30]);
            const uint16_t actual = Crc16((unsigned char*)&buf_byte_pack1, 30);
            if (actual == expected)
            {
                std::cout << "номер:" << (uint16_t)((buf[3] << 8) | buf[2]) << std::endl;
                std::cout << "время:" <<(uint32_t)((buf[7] << 24) | (buf[6] <<16) | (buf[5]<<8) | buf[4]);
                std::cout << "бме давл:" << read_float((const char*)&buf[8]);
                std::cout << "бме давление:" <<(uint32_t)((buf[12] << 24) | (buf[13] <<16) | (buf[14]<<8) | buf[15]);
                std::cout << "высота:" <<(uint16_t)((buf[16] << 8) | buf[17]);
                std::cout << "куки:" <<(uint16_t)((buf[18] << 8) | buf[19]);

                *fout <<(uint16_t)((buf[2] << 8) | buf[3]) << "," <<(uint32_t)((buf[4] << 24) | (buf[5] <<16) | (buf[6]<<8) | buf[7])<<","<<(uint32_t)((buf[8] << 24) | (buf[8] <<16) | (buf[10]<<8) | buf[11])<<","<<(uint32_t)((buf[12] << 24) | (buf[13] <<16) | (buf[14]<<8) | buf[15])<<","<<(uint16_t)((buf[16] << 8) | buf[17])<<","<<(uint16_t)((buf[18] << 8) | buf[19]) << std::endl;
            }
        }
        if (buf[i] = 0xfe)
        {
            for (int i = 0; i < 32; i++) buf_byte_pack2[i] = buf[i];
            if (Crc16((unsigned char *)&buf_byte_pack2, 30) == ((buf_byte_pack2[30] << 8) | buf_byte_pack2[31]))
            {
                std::cout << "номер:" <<(uint16_t)((buf[2] << 8) | buf[3]);
                std::cout << "время:" <<(uint32_t)((buf[4] << 24) | (buf[5] <<16) | (buf[6]<<8) | buf[7]);

                std::cout << "акселерометр:" <<(uint16_t)((buf[8] << 8) | buf[9]);
                std::cout << ":" <<(uint16_t)((buf[2] << 10) | buf[11]);
                std::cout << ":" <<(uint16_t)((buf[12] << 8) | buf[13]);

                std::cout << "гироскоп:" <<(uint16_t)((buf[14] << 8) | buf[15]);
                std::cout << ":" <<(uint16_t)((buf[16] << 8) | buf[17]);
                std::cout << ":" <<(uint16_t)((buf[18] << 8) | buf[19]);

                std::cout << "магнетометр:" <<(uint16_t)((buf[20] << 8) | buf[21]);
                std::cout << ":" <<(uint16_t)((buf[22] << 8) | buf[23]);
                std::cout << ":" <<(uint16_t)((buf[24] << 8) | buf[25]);

                std::cout << "фоторезистор:" <<(uint32_t)((buf[26] << 24) | (buf[27] <<16) | (buf[28]<<8) | buf[29]);
                std::cout << "состояние:" <<(uint8_t)(buf[30]);

                *fout <<(uint16_t)((buf[2] << 8) | buf[3])<<","<<(uint32_t)((buf[4] << 24) | (buf[5] <<16) | (buf[6]<<8) | buf[7])<<","<<(uint16_t)((buf[8] << 8) | buf[9])<<","<<(uint16_t)((buf[2] << 10) | buf[11])<<","<<(uint16_t)((buf[12] << 8) | buf[13])<<","<<(uint16_t)((buf[14] << 8) | buf[15])<<","<<(uint16_t)((buf[16] << 8) | buf[17])<<","<<(uint16_t)((buf[18] << 8) | buf[19]) << ",";
                *fout <<(uint16_t)((buf[20] << 8) | buf[21])<<","<<(uint16_t)((buf[22] << 8) | buf[23])<<","<<(uint16_t)((buf[24] << 8) | buf[25])<<","<<(uint32_t)((buf[26] << 24) | (buf[27] <<16) | (buf[28]<<8) | buf[29])<<","<<(uint8_t)(buf[30]) << std::endl;
            }

        }
    }
    return 0;
}

int main()
{

    uint8_t buf[400000];
    std::cout << "Hello World!\n";
    std::ofstream fout("testfile2.csv");
    std::ifstream fin("testfile.bin");
    for (int i = 0; fin.eof() == 0 && i < 400000; i++)
    {
        fin >> buf[i];
    }
    pars_b(buf, 400000, &fout);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
