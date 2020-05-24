#include<iostream>
#include<random>
#include<fstream>
#include <string>

const int key_upper_bound = 50000;
const int value_upper_bound = 1000088;

int main()
{
    // 产生两组随机数
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<float> key(0, key_upper_bound);
    std::uniform_int_distribution<int> value(0, value_upper_bound);

    int N; // 想要随机生成的测试数据大小
    std::cin >> N;

    // 生成对应的测试文件
    std::string file_name = "size=" + std::to_string(N) + ".txt";

    // 打开文件，向文件内输入随机产生的数据
    std::ofstream out_file(file_name, std::ios::out);
    for (int i = 0; i < N; i++)
    {
        out_file << key(mt) << " " << value(mt) << std::endl;
    }

    out_file.close(); // 关闭文件

    return 0;
}