// parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <fstream>
using namespace std;
#include <iostream>
#include <memory>
#include <vector>
#include <cstring>

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
    std::memcpy(ptr, data, 4);
    return retval;
}

unsigned short pars_packet_1_to_da(unsigned char* buf, size_t len, std::ofstream* fout_da_type_1)
{
                std::cout << "num:" << (uint16_t)((buf_byte_pack_da_1[3] << 8) | buf_byte_pack_da_1[2]) << std::endl;
                std::cout << "time:" << (uint32_t)((buf_byte_pack_da_1[7] << 24) | (buf_byte_pack_da_1[6] << 16) | (buf_byte_pack_da_1[5] << 8) | buf_byte_pack_da_1[4]) << std::endl;

                std::cout << "bme_pres:" << (uint32_t)((buf_byte_pack_da_1[11] << 24) | (buf_byte_pack_da_1[10] << 16) | (buf_byte_pack_da_1[9] << 8) | buf_byte_pack_da_1[8]) << std::endl;
                std::cout << "bme_temp:" << buf_byte_pack_da_1[12];
                std::cout << "bme_hum:" << (uint16_t)((buf_byte_pack2[14] << 8) | buf_byte_pack_da_1[13]) << std::endl;

                std::cout << "lsm_ac:" << (uint16_t)((buf_byte_pack_da_1[16] << 8) | buf_byte_pack_da_1[15]) << std::endl;
                std::cout << ":" << (uint16_t)((buf_byte_pack_da_1[18] << 8) | buf_byte_pack_da_1[17]) << std::endl;
                std::cout << ":" << (uint16_t)((buf_byte_pack_da_1[20] << 8) | buf_byte_pack_da_1[19]) << std::endl;

                std::cout << "lsm_gyro:" << (uint16_t)((buf_byte_pack_da_1[22] << 8) | buf_byte_pack_da_1[23]) << std::endl;
                std::cout << ":" << (uint16_t)((buf_byte_pack_da_1[24] << 8) | buf_byte_pack_da_1[23]) << std::endl;
                std::cout << ":" << (uint16_t)((buf_byte_pack2[26] << 8) | buf_byte_pack_da_1[25]) << std::endl;

                *fout_da_type_1 << (uint16_t)((buf_byte_pack2[3] << 8) | buf_byte_pack_da_1[2]) << ",";
                *fout_da_type_1 << (uint32_t)((buf_byte_pack_da_1[7] << 24) | (buf_byte_pack_da_1[6] << 16) | (buf_byte_pack_da_1[5] << 8) | buf_byte_pack_da_1[4]) << ",";
                *fout_da_type_1 << (uint32_t)((buf_byte_pack_da_1[11] << 24) | (buf_byte_pack_da_1[10] << 16) | (buf_byte_pack_da_1[9] << 8) | buf_byte_pack_da_1[8]) << ",";
                *fout_da_type_1 << (int)buf_byte_pack_da_1[12] << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[14] << 8) | buf_byte_pack_da_1[13]) << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[16] << 8) | buf_byte_pack_da_1[15]) << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[18] << 8) | buf_byte_pack_da_1[17]) << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[20] << 8) | buf_byte_pack_da_1[19]) << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[22] << 8) | buf_byte_pack_da_1[21]) << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[24] << 8) | buf_byte_pack_da_1[23]) << ",";
                *fout_da_type_1 << (uint16_t)((buf_byte_pack_da_1[26] << 8) | buf_byte_pack_da_1[25]) << std::endl;
}

unsigned short pars_packet_2_to_da(unsigned char* buf, size_t len, std::ofstream* fout_da_type_2)
{
                    std::cout << "num:" << (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2]) << std::endl;
                    std::cout << "time:" << (uint32_t)((buf_byte_pack_da_2[7] << 24) | (buf_byte_pack_da_2[6] << 16) | (buf_byte_pack_da_2[5] << 8) | buf_byte_pack_da_2[4]) << std::endl;

                    std::cout << read_float((const char*)&buf_byte_pack_da_2[8]) << std::endl;
                    std::cout << read_float((const char*)&buf_byte_pack_da_2[12]) << std::endl;
                    std::cout << read_float((const char*)&buf_byte_pack_da_2[16]) << std::endl;

                    std::cout << "fix" << (uint8_t)(buf_byte_pack_da_2[20]) << std::endl;
                    std::cout << "fstate" << (uint8_t)(buf_byte_pack_da_2[21]) << std::endl;

                    *fout_da_type_2 << (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2]) << ",";
                    *fout_da_type_2 << (uint32_t)((buf_byte_pack_da_2[7] << 24) | (buf_byte_pack_da_2[6] << 16) | (buf_byte_pack_da_2[5] << 8) | buf_byte_pack_da_2[4]) << ",";
                    *fout_da_type_2 << read_float((const char*)&buf_byte_pack_da_2[8])<< ",";
                    *fout_da_type_2 << read_float((const char*)&buf_byte_pack_da_2[12]) << ",";
                    *fout_da_type_2 << read_float((const char*)&buf_byte_pack_da_2[16) << ",";
                    *fout_da_type_2 << (int)(buf_byte_pack_da_2[20]) << ",";
                    *fout_da_type_2 << (int)(buf_byte_pack_da_2[21]) << std::endl;
}


unsigned short pars_b(unsigned char* buf, size_t len, std::ofstream* fout_ma_type_1, std::ofstream* fout_ma_type_2, std::ofstream* fout_da_1_type_1, std::ofstream* fout_da_1_type_2, std::ofstream* fout_da_2_type_1, std::ofstream* fout_da_2_type_2, std::ofstream* fout_da_3_type_1, std::ofstream* fout_da_3_type_2)
{
    for (size_t i = 0; i < len; i++)
    {
        uint8_t buf_byte_pack1[32];
        uint8_t buf_byte_pack2[32];
        uint8_t buf_byte_pack_da_1[32];
        uint8_t buf_byte_pack_da_2[32];

        if (buf[i] == 0xff && i + 31 < len)
        {
            for (size_t j = 0; j < 32; j++) buf_byte_pack1[j] = buf[j+i];
            const uint16_t expected = ((uint16_t)buf_byte_pack1[31] << 8) | (buf_byte_pack1[30]);
            const uint16_t actual = Crc16((unsigned char*)&buf_byte_pack1, 30);
            if (actual == expected)
            {
                std::cout << "num:" << (uint16_t)((buf_byte_pack1[2] << 8) | buf_byte_pack1[1]) << std::endl;
                std::cout << "time:" <<(uint32_t)((buf_byte_pack1[6] << 24) | (buf_byte_pack1[5] <<16) | (buf_byte_pack1[4]<<8) | buf_byte_pack1[3]) << std::endl;
                std::cout << "BME_peas:" << read_float((const char*)&buf_byte_pack1[7]) << std::endl;
                std::cout << "BME_temp:" << read_float((const char*)&buf_byte_pack1[11]) << std::endl;
                std::cout << "ds_temp:" << (uint16_t)((buf_byte_pack1[16] << 8) | buf_byte_pack1[15]) << std::endl;
                std::cout << "lat:" << read_float((const char*)&buf_byte_pack1[17]) << std::endl;
                std::cout << "long:" << read_float((const char*)&buf_byte_pack1[21]) << std::endl;
                std::cout << "height:" <<(uint16_t)((buf_byte_pack1[26] << 8) | buf_byte_pack1[25]) << std::endl;
                std::cout << "cookie:" <<(uint16_t)((buf_byte_pack1[28] << 8) | buf_byte_pack1[27]) << std::endl;

                *fout_ma_type_1 << (uint16_t)((buf_byte_pack1[2] << 8) | buf_byte_pack1[1]) << "," << (uint32_t)((buf_byte_pack1[6] << 24) | (buf_byte_pack1[5] << 16) | (buf_byte_pack1[4] << 8) | buf_byte_pack1[3]) << "," << read_float((const char*)&buf_byte_pack1[7]) << "," << read_float((const char*)&buf_byte_pack1[11]) << "," << (uint16_t)((buf_byte_pack1[16] << 8) | buf_byte_pack1[15]) << "," << read_float((const char*)&buf_byte_pack1[17]) << "," << read_float((const char*)&buf_byte_pack1[21]) << "," << (uint16_t)((buf_byte_pack1[26] << 8) | buf_byte_pack1[25]) << "," << (uint16_t)((buf_byte_pack1[28] << 8) | buf_byte_pack1[27]) << std::endl;
            }
            else 
            {
                cout << "num:" << " " << (uint16_t)((buf_byte_pack1[2] << 8) | buf_byte_pack1[1]) << " " << "exp:" << " " << expected << " " << "act:" << " " << actual << std::endl;
            }
        }

        if (buf[i] == 0xfe && i + 31 < len)
        {
            for (size_t j = 0; j < 32; j++) buf_byte_pack2[j] = buf[j + i];
            const uint16_t expected = ((uint16_t)buf_byte_pack2[31] << 8) | (buf_byte_pack2[30]);
            const uint16_t actual = Crc16((unsigned char*)&buf_byte_pack2, 30);
            if (actual == expected)
            {
                std::cout << "num:" << (uint16_t)((buf_byte_pack2[2] << 8) | buf_byte_pack2[1]) << std::endl;
                std::cout << "time:" <<(uint32_t)((buf_byte_pack2[6] << 24) | (buf_byte_pack2[5] <<16) | (buf_byte_pack2[4]<<8) | buf_byte_pack2[3]) << std::endl;

                std::cout << "acc:" <<(uint16_t)((buf_byte_pack2[8] << 8) | buf_byte_pack2[7]) << std::endl;
                std::cout << ":" <<(uint16_t)((buf_byte_pack2[10] << 10) | buf_byte_pack2[9]) << std::endl;
                std::cout << ":" <<(uint16_t)((buf_byte_pack2[12] << 8) | buf_byte_pack2[11]) << std::endl;

                std::cout << "gyro:" <<(uint16_t)((buf_byte_pack2[14] << 8) | buf_byte_pack2[13]) << std::endl;
                std::cout << ":" <<(uint16_t)((buf_byte_pack2[16] << 8) | buf_byte_pack2[15]) << std::endl;
                std::cout << ":" <<(uint16_t)((buf_byte_pack2[18] << 8) | buf_byte_pack2[17]) << std::endl;

                std::cout << "magn:" <<(uint16_t)((buf_byte_pack2[20] << 8) | buf_byte_pack2[19]) << std::endl;
                std::cout << ":" <<(uint16_t)((buf_byte_pack2[22] << 8) | buf_byte_pack2[21]) << std::endl;
                std::cout << ":" <<(uint16_t)((buf_byte_pack2[24] << 8) | buf_byte_pack2[23]) << std::endl;

                std::cout << "phot:" << read_float((const char*)&buf_byte_pack2[25]) << std::endl;
                std::cout << "state:" <<(int)(buf_byte_pack2[29]) << std::endl;



                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[2] << 8) | buf_byte_pack2[1]) << ",";
                *fout_ma_type_2 << (uint32_t)((buf_byte_pack2[6] << 24) | (buf_byte_pack2[5] << 16) | (buf_byte_pack2[4] << 8) | buf_byte_pack2[3]) << ",";

                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[8] << 8) | buf_byte_pack2[7]) << ",";
                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[10] << 10) | buf_byte_pack2[9]) << ",";
                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[12] << 8) | buf_byte_pack2[11]) << ",";

                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[14] << 8) | buf_byte_pack2[13]) << ",";
                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[16] << 8) | buf_byte_pack2[15]) << ",";
                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[18] << 8) | buf_byte_pack2[17]) << ",";

                *fout_ma_type_2 <<  (uint16_t)((buf_byte_pack2[20] << 8) | buf_byte_pack2[19]) << ",";
                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[22] << 8) | buf_byte_pack2[21]) << ",";
                *fout_ma_type_2 << (uint16_t)((buf_byte_pack2[24] << 8) | buf_byte_pack2[23]) << ",";

                *fout_ma_type_2 << read_float((const char*)&buf_byte_pack2[25]) << ",";
                *fout_ma_type_2 <<  (int)(buf_byte_pack2[29]) << std::endl;
                
            }
            else 
            {
                cout << "num:" <<  " " << (uint16_t)((buf_byte_pack2[2] << 8) | buf_byte_pack2[1]) << " " << "exp:" << " " << expected << " " << "act:" << " " << actual << std::endl;
            }

        }


        if (buf[i] == 0xfa && i + 27 < len)
        {
            for (size_t j = 0; j < 28; j++) buf_byte_pack_da_1[j] = buf[j + i];
            const uint16_t expected = ((uint16_t)buf_byte_pack_da_1[27] << 8) | (buf_byte_pack_da_1[26]);
            const uint16_t actual = Crc16((unsigned char*)&buf_byte_pack_da_1, 26);
            if (actual == expected) 
            {
                if(1 == (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2])) pars_packet_1_to_da(&buf_byte_pack_da_1, sizeof(buf_byte_pack_da_1), &fout_da_1_type_1);
                if(2 == (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2])) pars_packet_1_to_da(&buf_byte_pack_da_1, sizeof(buf_byte_pack_da_1), &fout_da_2_type_1);
                if(3 == (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2])) pars_packet_1_to_da(&buf_byte_pack_da_1, sizeof(buf_byte_pack_da_1), &fout_da_3_type_1);
            }
        }


        if (buf[i] == 0xfb && i + 22 < len)
        {
            if (buf[i + 1] == 1 && i + 22 < len)
            {

            
                for (size_t j = 0; j < 23; j++) buf_byte_pack_da_2[j] = buf[j + i];
                const uint16_t expected = ((uint16_t)buf_byte_pack_da_2[22] << 8) | (buf_byte_pack_da_2[21]);
                const uint16_t actual = Crc16((unsigned char*)&buf_byte_pack_da_2, 21);
                if (actual == expected) 
                {
                if(1 == (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2])) pars_packet_2_to_da(&buf_byte_pack_da_2, sizeof(buf_byte_pack_da_2), &fout_da_1_type_1);
                if(2 == (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2])) pars_packet_2_to_da(&buf_byte_pack_da_2, sizeof(buf_byte_pack_da_2), &fout_da_2_type_1);
                if(3 == (uint16_t)((buf_byte_pack_da_2[3] << 8) | buf_byte_pack_da_2[2])) pars_packet_2_to_da(&buf_byte_pack_da_2, sizeof(buf_byte_pack_da_2), &fout_da_3_type_1);
                }

            }
        }
    }
    return 0;
}

int main()
{
    const size_t buffer_size = 40000000;
    std::vector<uint8_t> buffer(buffer_size);

    std::cout << "Hello World!\n";
    std::ofstream fout_ma_type_1("testfile_ma_type_1.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_ma_type_2("testfile_ma_type_2.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_da_1_type_1("testfile_da_1_type_1.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_da_1_type_2("testfile_da_1_type_2.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_da_2_type_1("testfile_da_2_type_1.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_da_2_type_2("testfile_da_2_type_2.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_da_3_type_1("testfile_da_3_type_1.csv", std::ios::out | std::ios::trunc);
    std::ofstream fout_da_3_type_2("testfile_da_3_type_2.csv", std::ios::out | std::ios::trunc);
    std::ifstream fin("testfile.bin", std::ios::binary | std::ios::in);

    while (1)
    {
        fin.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        size_t readed = fin.gcount();
        buffer.resize(readed);
        std::cout << "size: " << buffer.size();
        if (0 == buffer.size())
            break;

        pars_b(buffer.data(), buffer.size(), &fout_ma_type_1, &fout_ma_type_2, &fout_da_type_1, &fout_da_type_2);
    }
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
