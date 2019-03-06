#include <algorithm>
#include <ctime>
#include <iostream>

int main()
{
    const unsigned arrSize = 32768;
    int data[arrSize] = {0};

    // 随机填充0~256间的整数,为了方便结果对比此处未加入随机种子
    for (unsigned int idx = 0; idx < arrSize; ++idx)
        data[idx] = std::rand() % 256;


    // 观察排序对求和计算的影响
    std::sort(data, data + arrSize);

    //开始验证
    unsigned long long sum = 0;
    clock_t startTime2 = clock();

    //此处为了加强对比效果，将求和计算循环执行了10万次
    for (unsigned int i = 0; i < 100000; ++i)
    {
        for (unsigned int idx = 0; idx < arrSize; ++idx)
        {
            if (data[idx] >= 128)
                sum += data[idx];
        }
    }

    // 将执行时间转化为秒数
    double elapsedTime2 = static_cast<double>(clock() - startTime2) / CLOCKS_PER_SEC;

    std::cout << "排序执行时间： " << elapsedTime2 << std::endl;
    std::cout << "数值总和: " << sum <<std::endl;


    return 0;
}
