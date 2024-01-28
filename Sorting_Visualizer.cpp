//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              HEADER FILES                                                    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <SDL.h>
#include <time.h>
#include <limits>
#include <fstream>
using namespace std;


class SortingVisualizer
{
private:
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                              SCREEN SIZE, ARRAY SIZE AND RECTANGLE WEIGHT DECLARATION                        //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const int SCREEN_WIDTH = 910;
    const int SCREEN_HEIGHT = 750;

    static const int arrSize = 130;
    const int rectSize = 7;
    static int arr[arrSize];
    static int Barr[arrSize];




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                              SDL INITIALIZATION                                              //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool complete;

public:
    SortingVisualizer() : window(nullptr), renderer(nullptr), complete(false) {}

    ~SortingVisualizer()
    {
        close();
    }

    bool init()
    {
        bool success = true;
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "Couldn't initialize SDL. SDL_Error: " << SDL_GetError();
            success = false;
        }
        else
        {
            window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == nullptr)
            {
                std::cout << "Couldn't create window. SDL_Error: " << SDL_GetError();
                success = false;
            }
            else
            {
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                if (renderer == nullptr)
                {
                    std::cout << "Couldn't create renderer. SDL_Error: " << SDL_GetError();
                    success = false;
                }
            }
        }
        return success;
    }

    void close()
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_Quit();
    }

    void visualize(int x = -1, int y = -1, int z = -1)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        int j = 0;
        for (int i = 0; i <= SCREEN_WIDTH - rectSize; i += rectSize)
        {
            SDL_PumpEvents();

            SDL_Rect rect = { i, 0, rectSize, arr[j] };

            if (complete)
            {
                SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else if (j == x || j == z)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
                SDL_RenderFillRect(renderer, &rect);
            }
            else if (j == y)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
                SDL_RenderDrawRect(renderer, &rect);
            }
            j++;
        }
        SDL_RenderPresent(renderer);
    }

    void randomizeAndSaveArray()
    {
        ifstream inputFile("Data_File.txt");
        if (!inputFile.is_open())
        {
            cout << "Error opening Data_File.txt\n";
            exit(1);
        }

        for (int i = 0; i < arrSize; i++)
        {
            int value;
            if (!(inputFile >> value))
            {
                cout << "Error reading value from Data_File.txt\n";
                exit(1);
            }
            Barr[i] = value;
        }

        inputFile.close();
    }

    void loadArr()
    {
        memcpy(arr, Barr, sizeof(int) * arrSize);
    }

    void execute()
    {
        if (!init())
        {
            cout << "SDL Initialization Failed.\n";
        }
        else
        {
            randomizeAndSaveArray();
            loadArr();
            const auto start = std::chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed;

            SDL_Event e;
            bool quit = false;




            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //                                    SORTING ALGORITHM EXECUTION                                               //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                        complete = false;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_q:
                            quit = true;
                            complete = false;
                            cout << "\n\nEXITING SORTING VISUALIZER.\n";
                            break;

                        case SDLK_0:
                            randomizeAndSaveArray();
                            complete = false;
                            loadArr();
                            cout << "\n\nNEW RANDOM LIST GENERATED.\n";
                            break;

                        case SDLK_1:
                            loadArr();
                            cout << "\n\nSELECTION SORT STARTED." << endl;
                            complete = false;
                            elapsed = std::chrono::high_resolution_clock::now() - start;
                            selectionSort();
                            complete = true;
                            cout << "SELECTION SORT COMPLETE." << endl;
                            std::cout << "Total Time:\t" << elapsed.count() << " s\n";
                            break;

                        case SDLK_2:
                            loadArr();
                            cout << "\n\nINSERTION SORT STARTED." << endl;
                            complete = false;
                            elapsed = std::chrono::high_resolution_clock::now() - start;
                            insertionSort();
                            complete = true;
                            cout << "INSERTION SORT COMPLETE." << endl;
                            std::cout << "Total Time:\t" << elapsed.count() << " s\n";
                            break;

                        case SDLK_3:
                            loadArr();
                            cout << "\n\nBUBBLE SORT STARTED." << endl;
                            complete = false;
                            elapsed = std::chrono::high_resolution_clock::now() - start;
                            bubbleSort();
                            complete = true;
                            cout << "BUBBLE SORT COMPLETE." << endl;
                            std::cout << "Total Time:\t" << elapsed.count() << " s\n";
                            break;

                        case SDLK_4:
                            loadArr();
                            cout << "\n\nMERGE SORT STARTED." << endl;
                            complete = false;
                            elapsed = std::chrono::high_resolution_clock::now() - start;
                            mergeSort(arr, 0, arrSize - 1);
                            complete = true;
                            cout << "MERGE SORT COMPLETE." << endl;
                            std::cout << "Total Time:\t" << elapsed.count() << " s\n";
                            break;

                        case SDLK_5:
                            loadArr();
                            cout << "\n\nQUICK SORT STARTED." << endl;
                            complete = false;
                            elapsed = std::chrono::high_resolution_clock::now() - start;
                            quickSort(arr, 0, arrSize - 1);
                            complete = true;
                            cout << "QUICK SORT COMPLETE." << endl;
                            std::cout << "Total Time:\t" << elapsed.count() << " s\n";
                            break;

                        case SDLK_6:
                            loadArr();
                            cout << "\n\nHEAP SORT STARTED." << endl;
                            complete = false;
                            elapsed = std::chrono::high_resolution_clock::now() - start;
                            inplaceHeapSort(arr, arrSize);
                            complete = true;
                            cout << "HEAP SORT COMPLETE." << endl;
                            std::cout << "Total Time:\t" << elapsed.count() << " s\n";
                            break;
                        }
                    }
                }
                visualize();
            }
            close();
        }
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                            SELECTION SORT ALGORITHM                                          //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void selectionSort()
    {
        int minIndex;
        for (int i = 0; i < arrSize - 1; i++)
        {
            minIndex = i;
            for (int j = i + 1; j < arrSize; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                    visualize(i, minIndex);
                }
                SDL_Delay(1);
            }
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                            INSERTION SORT ALGORITHM                                          //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void insertionSort()
    {
        for (int i = 1; i < arrSize; i++)
        {
            int j = i - 1;
            int temp = arr[i];
            while (j >= 0 && arr[j] > temp)
            {
                arr[j + 1] = arr[j];
                j--;

                visualize(i, j + 1);
                SDL_Delay(5);
            }
            arr[j + 1] = temp;
        }
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                            BUBBLE SORT ALGORITHM                                             //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void bubbleSort()
    {
        for (int i = 0; i < arrSize - 1; i++)
        {
            for (int j = 0; j < arrSize - 1 - i; j++)
            {
                if (arr[j + 1] < arr[j])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;

                    visualize(j + 1, j, arrSize - i);
                }
                SDL_Delay(1);
            }
        }
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                            MERGE SORT ALGORITHM                                              //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void merge2SortedArrays(int a[], int si, int ei)
    {
        int size_output = (ei - si) + 1;
        int* output = new int[size_output];

        int mid = (si + ei) / 2;
        int i = si, j = mid + 1, k = 0;
        while (i <= mid && j <= ei)
        {
            if (a[i] <= a[j])
            {
                output[k] = a[i];
                visualize(i, j);
                i++;
                k++;
            }
            else
            {
                output[k] = a[j];
                visualize(i, j);
                j++;
                k++;
            }
        }
        while (i <= mid)
        {
            output[k] = a[i];
            visualize(-1, i);
            i++;
            k++;
        }
        while (j <= ei)
        {
            output[k] = a[j];
            visualize(-1, j);
            j++;
            k++;
        }
        int x = 0;
        for (int l = si; l <= ei; l++)
        {
            a[l] = output[x];
            visualize(l);
            SDL_Delay(15);
            x++;
        }
        delete[] output;
    }

    void mergeSort(int a[], int si, int ei)
    {
        if (si >= ei)
        {
            return;
        }
        int mid = (si + ei) / 2;

        mergeSort(a, si, mid);
        mergeSort(a, mid + 1, ei);

        merge2SortedArrays(a, si, ei);
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                            QUICK SORT ALGORITHM                                              //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int partition_array(int a[], int si, int ei)
    {
        int count_small = 0;

        for (int i = (si + 1); i <= ei; i++)
        {
            if (a[i] <= a[si])
            {
                count_small++;
            }
        }
        int c = si + count_small;
        int temp = a[c];
        a[c] = a[si];
        a[si] = temp;
        visualize(c, si);

        int i = si, j = ei;

        while (i < c && j > c)
        {
            if (a[i] <= a[c])
            {
                i++;
            }
            else if (a[j] > a[c])
            {
                j--;
            }
            else
            {
                int temp_1 = a[j];
                a[j] = a[i];
                a[i] = temp_1;

                visualize(i, j);
                SDL_Delay(70);

                i++;
                j--;
            }
        }
        return c;
    }

    void quickSort(int a[], int si, int ei)
    {
        if (si >= ei)
        {
            return;
        }

        int c = partition_array(a, si, ei);
        quickSort(a, si, c - 1);
        quickSort(a, c + 1, ei);
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                            HEAP SORT ALGORITHM                                               //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void inplaceHeapSort(int* input, int n)
    {
        for (int i = 1; i < n; i++)
        {
            int childIndex = i;
            int parentIndex = (childIndex - 1) / 2;

            while (childIndex > 0)
            {
                if (input[childIndex] > input[parentIndex])
                {
                    int temp = input[parentIndex];
                    input[parentIndex] = input[childIndex];
                    input[childIndex] = temp;
                }
                else
                {
                    break;
                }

                visualize(parentIndex, childIndex);
                SDL_Delay(40);

                childIndex = parentIndex;
                parentIndex = (childIndex - 1) / 2;
            }
        }

        for (int heapLast = n - 1; heapLast >= 0; heapLast--)
        {
            int temp = input[0];
            input[0] = input[heapLast];
            input[heapLast] = temp;

            int parentIndex = 0;
            int leftChildIndex = 2 * parentIndex + 1;
            int rightChildIndex = 2 * parentIndex + 2;

            while (leftChildIndex < heapLast)
            {
                int maxIndex = parentIndex;

                if (input[leftChildIndex] > input[maxIndex])
                {
                    maxIndex = leftChildIndex;
                }
                if (rightChildIndex < heapLast && input[rightChildIndex] > input[maxIndex])
                {
                    maxIndex = rightChildIndex;
                }
                if (maxIndex == parentIndex)
                {
                    break;
                }

                int temp = input[parentIndex];
                input[parentIndex] = input[maxIndex];
                input[maxIndex] = temp;

                visualize(maxIndex, parentIndex, heapLast);
                SDL_Delay(40);

                parentIndex = maxIndex;
                leftChildIndex = 2 * parentIndex + 1;
                rightChildIndex = 2 * parentIndex + 2;
            }
        }
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                          INTRODUCTION WINDOW                                                 //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void intro()
    {
        cout << "==============================Sorting Visualizer==============================\n\n"
            << "Visualization of different sorting algorithms in C++ with SDL2 Library.\n\n"
            << "A sorting algorithm is an algorithm that puts the elements of a list in a certain order.\n"
            << "While there are a large number of sorting algorithms, in practical implementations, a few algorithms predominate.\n\n"
            << "In this implementation of sorting visualizer, we'll be looking at some of these sorting algorithms.\n"
            << "The sorting algorithms covered here are Selection Sort, Insertion Sort, Bubble Sort, Merge Sort, Quick Sort, and Heap Sort.\n"
            << "The list size is fixed to 130 elements.\n"
            << "You can randomize the list and select any type of sorting algorithm to call on the list from the given options.\n"
            << "Here, all sorting algorithms will sort the elements in ascending order.\n"
            << "The sorting time being visualized for an algorithm is not exactly the same as their actual time complexities.\n"
            << "The relatively faster algorithms like Merge Sort, etc., have been delayed so that they could be properly visualized.\n\n"
            << "Press ENTER to show controls...";

        string s;
        getline(cin, s);
        if (s.empty())
        {
            return;
        }
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                    SORTING ALGORITHM EXECUTION CONTROL
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void controls()
    {
        cout << "\n\nWARNING: Please give a new command only after the current command's execution is done.\n\n"
            << "CONTROL MENU:-\n"
            << "    Use 1 to start Selection Sort Algorithm." << endl
            << "    Use 2 to start Insertion Sort Algorithm." << endl
            << "    Use 3 to start Bubble Sort Algorithm." << endl
            << "    Use 4 to start Merge Sort Algorithm." << endl
            << "    Use 5 to start Quick Sort Algorithm." << endl
            << "    Use 6 to start Heap Sort Algorithm." << endl
            << "PRESS ENTER TO START SORTING VISUALIZER...\n" << endl
            << "Or type -1 and press ENTER to quit the program.";

        string s;
        getline(cin, s);
        if (s == "-1")
        {
            exit(0);
        }
    }
};

int SortingVisualizer::arr[arrSize];
int SortingVisualizer::Barr[arrSize];




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             MAIN DRIVER CODE                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* args[])
{
    SortingVisualizer visualizer;
    visualizer.intro();

    while (true)
    {
        cout << endl;
        visualizer.controls();
        visualizer.execute();
    }

    return 0;
}