#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <math.h>
#include <ctime>
#include <string>
#include <vector>

using namespace cv;

void print(std::list<int> const& list)
{
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void save_to_file(std::list<int> const& list, int x)
{
    std::ofstream file("wynik.txt");
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        file << *it << std::endl;
        if (x == 1)
            break;
        x--;
    }
    file.close();
}

int pobierz(std::list<int>& list, int el)
{
    int tmp{ 0 };
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        if (el == tmp)
            return *it;
        tmp++;
    }

}

void calc(std::list<int> const& list)
{
    std::ofstream file("losowe_liczby.txt");
    int number = 0, temp = 7, bit = 0;
    for (auto it = list.cbegin(); it != list.cend(); it++)
    {
        bit = *it;
        //std::cout << bit;
        bit <<= temp;
        number = number | bit;
        temp--;
        if (temp < 0)
        {
            temp = 7;
            file << number << std::endl;
            //std::cout << std::endl << number << std::endl;
            number = 0;
            //  break;
        }
    }
    file.close();
}

int flip(int num)
{
    if (num == 1)
        return 0;
    else
        return 1;
}

void TRNG(int bitAmount)
{
    clock_t start;
    std::list<int> subList{ };
    std::list<int> finalList{ };
    int frameNum = 0;
    int size{ 16 }; 

    Point3_<uchar>* p;
    //taking photo
    VideoCapture camera(0);
    camera.set(CAP_PROP_FRAME_WIDTH, 1920);
    camera.set(CAP_PROP_FRAME_HEIGHT, 1080);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return;
    }

    Mat img;
    do
    {
        for (int i = 0; i < 4; i++)
        {
            camera >> img;
            if (img.empty())
            {
                std::cout << "Could not read the image " << std::endl;
                return;
            }

            frameNum++;

            for (int i = 0; i < img.rows; i++)
            {
                for (int j = 0; j < img.cols; j++)
                {
                    p = img.ptr<Point3_<uchar> >(i, j);
                    int siatka = 0x0001;

                    if ((int)p->x > 1 && (int)p->x < 254)
                    {
                        if (frameNum % 2 == 0)
                            subList.push_back(flip(siatka & (int)p->x));
                        else
                            subList.push_back(siatka & (int)p->x);
                    }

                    if ((int)p->y > 1 && (int)p->y < 254)
                    {
                        if (frameNum % 2 == 0)
                            subList.push_back(flip(siatka & (int)p->y));
                        else
                            subList.push_back(siatka & (int)p->y);
                    }

                    if ((int)p->z > 1 && (int)p->z < 254)
                    {
                        if (frameNum % 2 == 0)
                            subList.push_back(flip(siatka & (int)p->z));
                        else
                            subList.push_back(siatka & (int)p->z);
                    }
                }
            }
        }
    } while (subList.size() < bitAmount);

    auto it = subList.cbegin();
    size = ceil(sqrt(bitAmount));
    //tworzenie tablicy
    int** tab{ new int* [size] };
    for (int i = 0; i < size; i++)
    {
        tab[i] = new int[size];
    }

    int z{ 0 };
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tab[j][i] = *it;
            it++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            finalList.push_back(tab[i][j]);
        }
    }

    for (int i = 0; i < size; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;
}

void DES(std::string message)
{
    std::vector<uint64_t> choppedMessage;
    uint16_t block;
    int j = 0;

    for (int i = 0; i < message.length(); i++)
    {    
        while(j % 8 == 0)
        if (i % 8 == 0)
        {
            choppedMessage.push_back(block);
        }
        block = block | message[i];
        block << 8;
    }

    while ()
    {

    }
}

int main()
{
    std::string message;

    std::cout << "Podaj tekst, ktory chcesz zakodowac: ";
    std::cin >> message;


}

