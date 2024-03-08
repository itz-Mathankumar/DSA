#include <bits/stdc++.h>

template <typename T>

class DynamicArray
{

private:

    T* array;
    int arrayCapacity;
    int arrayInitialCapacity = 16;
    int arrayLength;

    int CheckIfValueIsPresentInArray(T data){
        for(int index = 0; index < this->arrayLength; index++){
            if(this->array[index] == data){
                return index;
            } 
        }

        return -1;
    }

    void CheckIfIndexIsValid(int index){
        if (index < 0 || index >= this->arrayLength){
            throw std::invalid_argument("Invalid Index: " + std::to_string(index));
        }
    }

    void DoubleArrayCapacity()
    {
        if (this->arrayCapacity == 0){
            this->arrayCapacity = 1;
        }
        else{
            this->arrayCapacity *= 2;
        }
    }

public:

    DynamicArray()
    {
        DynamicArray(this->arrayInitialCapacity);
    }

    DynamicArray(int capacity)
    {
        if (capacity < 0){
            std::cout << "The given arrayCapacity is invalid. Using default capacity of " << this-arrayInitialCapacity;
            capacity = this->arrayInitialCapacity;
        }

        this->arrayCapacity = capacity;
        this->array = new T[capacity];
    }

    int size(){
        return this->arrayLength;
    }

    bool IsEmpty(){
        return this->size == 0;
    }

    T get(int index)
    {
        this->CheckIfIndexIsValid(index);
        return this->array[index];
    }

    void set(int index, T element){
        this->CheckIfIndexIsValid(index);
        this->array[index] = element;
    }

    void Clear(){
        for (int index = 0; index < this->arrayLength; index++){
            this->array[index] = T();
        }

        this->arrayLength = 0;
    }

    void add(T element){
        if(this->arrayLength + 1 > arrayCapacity){
            this->DoubleArrayCapacity();
            T* newArray = new T[this->arrayCapacity];
            std::memcpy(newArray, this->array, this->arrayLength * sizeof(T));
            delete[] array;
            this->array = newArray;
        }

        this->array[arrayLength++] = element;
    }

    void removeAt(int index){
        this->CheckIfIndexIsValid(index);
        T* newArray = new T[arrayLength - 1];
        for (int front = 0, back = 0; front <= this->arrayLength; front++, back++){
            if (front == index) back--;
            else newArray[back] = this->array[front];
        }

        delete[] this->array;
        this->array = newArray;
        this->arrayCapacity = --this->arrayLength;
    }

    void remove(T data){
        int index = this->indexOf(data);
        this->removeAt(index);
    }

    int indexOf(T data){
        int index = this->CheckIfValueIsPresentInArray(data);
        if(index == -1){
            throw std::invalid_argument("Invalid value: " + std::to_string(data));
        }

        return index;
    }

    bool contains(T data){
        return CheckIfValueIsPresentInArray(data) >= 0;
    }

    class Iterator{
    private:
        int index;
    
    public:
        Iterator() : index(0) {}

        bool hasNext(){
            return index < this->arrayLength;
        } 

        T next() {
            return array[index++];
        }
    };

    Iterator iterator() {
        return Iterator();
    }

    std::string to_string(){
        if(this->arrayLength == 0) {
            return "[]";
        }

        std::string result = "[";
        for (int index = 0; index < this->arrayLength - 1; index++){
            result += std::to_string(array[index]) + ", ";
        }

        result += std::to_string(array[this->arrayLength - 1]) + "]";
        return result;
    }

    ~DynamicArray(){
        delete[] array;
    }
};

int main()
{
    std::cout << "Welcome to Dynamic Array Implementation";
    DynamicArray<int> myArray; 
    myArray.add(1);
    myArray.add(2);
    std::cout << '\n';
    std::cout << myArray.contains(1);
    std::cout << '\n';
    std::cout << myArray.contains(11);
    std::cout << '\n';
    std::cout << myArray.indexOf(2);
    std::cout << '\n';
    std::cout << myArray.size();
    std::cout << '\n';
    std::cout << myArray.to_string();
    std::cout << '\n';
    std::cout << myArray.get(0);
    myArray.remove(1);
    std::cout << '\n';
    std::cout << myArray.get(0);
    std::cout << '\n';

    return 0;
}
