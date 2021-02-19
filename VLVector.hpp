/** @file VLVector.hpp
* @author  Yair Escott <yair.95@gmail.com>
* @brief the 2020 exam C++
*/
// ------------------------------ includes ------------------------------
#ifndef EXAM_VLVECTOR_HPP
#define EXAM_VLVECTOR_HPP

#include <cstddef>
#include <new>
#include <string>
#include <cmath>
#include <exception>
#include <iostream>
using namespace std;
// ------------------------------the class  -----------------------------
/**
 * @brief the VLVector class
 * @tparam T the type of items stored
 * @tparam C the capacity on the stack
 */
template<class T, size_t C = 16> class VLVector
{
public:

/**
     * @brief nested class of a non constant iterator
     */
    class Iterator
    {
    public:
        /**
         * @brief constructor for the iterator
         * @param Pointer recieves a pointer to a T object
         */
        explicit Iterator(T* Pointer) : cur(Pointer){ }

        /**
         * @brief returns an iterator at the specified amount of steps away from the start
         * @param diff the number of steps
         * @return the new iterator
         */
        Iterator operator +(const int diff)
        {
            return Iterator(cur + diff);
        }

        /**
         * @brief sets an iterator to be like the other
         * @param iter the iterater to copy
         * @return the updated iterator
         */
        Iterator & operator =(const Iterator & iter)
        {
            this-> cur = iter.cur;
            return *this;
        }

        /**
          * @brief returns an iterator at the specified amount of steps away from the start
          * @param diff the number of steps
          * @return the new iterator
          */
        Iterator operator -(const int diff)
        {
            return Iterator(cur - diff);
        }

        /**
         * @brief checks if one iterator is larger that the next
         * @param iterator the other iterator
         * @return true if yes and false if no
         */
        bool operator >(const Iterator& iterator)
        {
            return *cur > *iterator.cur;
        }

        /**
         * @brief checks if one iterator is smaller that the next
         * @param iterator the other iterator
         * @return true if yes and false if no
         */
        bool operator <(const Iterator& iterator)
        {
            return *cur < *iterator.cur;
        }

        /**
         * @brief checks if one iterator is larger or equal that the next
         * @param iterator the other iterator
         * @return true if yes and false if no
         */
        bool operator >=(const Iterator& iterator)
        {
            return *cur >= *iterator.cur;
        }

        /**
         * @brief checks if one iterator is smaller or equal that the next
         * @param iterator the other iterator
         * @return true if yes and false if no
         */
        bool operator <=(const Iterator& iterator)
        {
            return *cur <= *iterator.cur;
        }

        /**
         * @brief returns the item in the index of the iterator
         * @param diff the index
         * @return the item
         */
        T& operator [](const int diff)
        {
            return cur[diff];
        }

        /**
         * @brief updated the iterator to a new object
         * @param diff the number of paces to go
         * @return the iterator
         */
        Iterator& operator +=(const int diff)
        {
            cur += diff;
            return *this;
        }

        /**
        * @brief updated the iterator to a new object
        * @param diff the number of paces to go
        * @return the iterator
        */
        Iterator& operator -=(const int diff)
        {
            cur -= diff;
            return *this;
        }

        /**
         * @return the pointer to the beginning of the array
         */
        T* operator->()
        {
            return cur;
        }

        /**
         * @return updates the iterator then returns the original iterator
         */
        Iterator operator++()
        {
            Iterator i(*this);
            cur++;
            return i;
        }

        /**
         * @return updates the iterator the specified number of steps then returns the original
         * iterator
         */
         Iterator operator++(int)
        {
            Iterator prev(*this);
            ++(*this);
            return prev;
        }

        /**
         * @return updates the iterator the specified number of steps then returns the original
         * iterator
         */
        Iterator operator--(int)
        {
            Iterator prev(*this);
            --(*this);
            return prev;
        }

        /**
         * @return updates the iterator then returns the original iterator
         */
        Iterator operator--()
        {
            Iterator i = *this;
            cur--;
            return i;
        }

        /**
         * @brief dereference
         * @return returnst the T object that the iter was pointing at
         */
        T& operator*()
        {
            return *cur;
        }

        /**
         * @brief checks if two iter are pointing to the same object
         * @param obj the second iter
         * @return true if yes an false if no
         */
        bool operator==(const Iterator& obj)
        {
            return *cur == *obj.cur;
        }

        /**
         * @brief checks if two iter are not pointing to the same object
         * @param obj the second iter
         * @return true if yes an false if no
         */
        bool operator!=(const Iterator obj)
        {
            return *cur != *obj.cur;
        }

    private:
        /**
         * @brief the pointer to the T object
         */
        T* cur;
    };

    /**
    * @brief nested class of a constant iterator
    */
    class constIterator
    {
    public:

        /**
         * @brief constructor for the const iterator
         * @param Pointer recieves a pointer to a T object
         */
        explicit constIterator(const T* Pointer) : cur(Pointer){ }

        /**
       * @brief returns an iterator at the specified amount of steps away from the start
       * @param diff the number of steps
       * @return the new iterator
       */
        constIterator operator +(const int diff) const
        {
            return constIterator(cur + diff);
        }

        /**
         * @brief sets an iterator to be like the other
         * @param iter the iterater to copy
         * @return the updated iterator
         */
        constIterator & operator =(constIterator & iter)
        {
            this-> cur = iter.cur;
            return *this;
        }

        /**
         * @brief returns an iterator at the specified amount of steps away from the start
         * @param diff the number of steps
         * @return the new iterator
         */
        constIterator operator -(int diff) const
        {
            return constIterator(cur - diff);
        }

        /**
        * @brief checks if one iterator is larger that the next
        * @param iterator the other iterator
        * @return true if yes and false if no
        */
        bool operator >(constIterator& iterator)
        {
            return *cur > *iterator.cur;
        }

        /**
        * @brief checks if one iterator is smaller that the next
        * @param iterator the other iterator
        * @return true if yes and false if no
        */
        bool operator <(constIterator& iterator)
        {
            return *cur < *iterator.cur;
        }

        /**
        * @brief checks if one iterator is larger or equal that the next
        * @param iterator the other iterator
        * @return true if yes and false if no
        */
        bool operator >=(constIterator& iterator)
        {
            return *cur >= *iterator.cur;
        }

        /**
        * @brief checks if one iterator is smaller or equal that the next
        * @param iterator the other iterator
        * @return true if yes and false if no
        */
        bool operator <=(constIterator& iterator)
        {
            return *cur <= *iterator.cur;
        }

        /**
        * @brief returns the item in the index of the iterator
        * @param diff the index
        * @return the item
        */
        const T& operator[](const int diff) const
        {
            return cur[diff];
        }

        /**
        * @brief updated the iterator to a new object
        * @param diff the number of paces to go
        * @return the iterator
        */
        constIterator& operator +=(const int diff)
        {
            cur += diff;
            return *this;
        }

        /**
       * @brief updated the iterator to a new object
       * @param diff the number of paces to go
       * @return the iterator
       */
        constIterator& operator -=(const int diff)
        {
            cur -= diff;
            return *this;
        }

        /**
        * @return the pointer to the beginning of the array
        */
        const T* operator->() const
        {
            return cur;
        }

        /**
        * @return updates the iterator then returns the original iterator
        */
        constIterator operator++()
        {
            constIterator i = *this;
            cur++;
            return i;
        }
        /**
         * @return updates the iterator the specified number of steps then returns the original
         * iterator
         */
        constIterator operator++(int)
        {
            constIterator prev(*this);
            ++(*this);
            return prev;
        }

        /**
         * @return updates the iterator the specified number of steps then returns the original
         * iterator
         */
        constIterator operator--(int)
        {
            constIterator prev(*this);
            --(*this);
            return prev;
        }
        /**
         * @return updates the iterator then returns the original iterator
         */
        constIterator operator--()
        {
            constIterator i = *this;
            cur--;
            return i;
        }

        /**
         * @brief dereference
         * @return returnst the T object that the iter was pointing at
         */
        const T& operator*() const
        {
            return *cur;
        }

        /**
        * @brief checks if two iter are pointing to the same object
        * @param obj the second iter
        * @return true if yes an false if no
        */
        bool operator==(constIterator& obj)
        {
            return *cur == *obj.cur;
        }

        /**
        * @brief checks if two iter are not pointing to the same object
        * @param obj the second iter
        * @return true if yes an false if no
        */
        bool operator!=(constIterator obj)
        {
            return *cur != *obj.cur;
        }

    private:
        /**
        * @brief the pointer to the T object
        */
        const T* cur;
    };

    /**
     * @return returns an iterator pointing to the first object
     */
    Iterator begin()
    {
        if(this->_isDynamic)
        {
            return Iterator(this->_dataDynamic);
        }
        else
        {
            return Iterator(this->_dataC);

        }
    }

    /**
    * @return returns an iterator pointing to the last object
    */
    Iterator end()
    {
        if(this->_isDynamic)
        {
            return Iterator(this->_dataDynamic) + this->_size;

        }
        else
        {
            return Iterator(this->_dataC) + this->_size;

        }
    }

    /**
     * @return returns a const iterator pointing to the first object
     */
    constIterator cbegin() const
    {
        if(this->_isDynamic)
        {
            return constIterator(this->_dataDynamic);
        }
        else
        {
            return constIterator(this->_dataC);
        }
    }

    /**
  * @return returns a const iterator pointing to the last object
  */
    constIterator cend() const
    {
        if(this->_isDynamic)
        {
            return constIterator(this->_dataDynamic) + this->_size;

        }
        else
        {
            return constIterator(this->_dataC) + this->_size;

        }
    }

    /**
     * @brief a VLVector constructor that receives 2 iterators of T and adds the items between
     * them to the VLV
     * @tparam InputIterator the iterator type
     * @param first the left placemet
     * @param last the right placement
     */
    template<class InputIterator>
    VLVector(InputIterator first, InputIterator last):_size(0), _capacity(C)
    {
        while(first != last)
        {
            this->push_back(*first);
            first++;
        }
    }

    /**
     * @brief the default constructor
     */
    VLVector(): _size(0), _capacity(C){}

    /**
     * @brief the copy const'
     * @param toCopy the const' to copy
     */
    VLVector(VLVector<T, C>& toCopy):_size(toCopy._size), _capacity(toCopy._capacity)
    {

        if(!toCopy.empty())
        {
            if(toCopy._isDynamic)
            {
                this->_isDynamic = true;
                T* temp;
                temp = new (nothrow)T[toCopy._capacity];
                if (temp != nullptr)
                {
                    this->_dataDynamic = temp;
                    for (size_t i = 0; i < size(); i++)
                    {
                        this->_dataDynamic[i] = toCopy.at(i);
                    }
                }
            }
            else
            {
                this->_isDynamic = false;
                for(size_t i = 0; i < this->_size; i++)
                {
                    this->_dataC[i] = toCopy.at(i);
                }
            }
        }
        else
        {
            this->_isDynamic = false;
        }
    }

    /**
     * the destructor
     */
    ~VLVector()
    {
        if(this->_isDynamic)
        {
            delete [] this->_dataDynamic;
            this->_dataDynamic = NULL;
        }
    }

    /**
     * @return the size of the VLVector
     */
    size_t size()
    {
        return this->_size;
    }

    /**
     * @return the current capacity of the vector
     */
    size_t capacity()
    {
        return this->_capacity;
    }

    /**
     * @return true if the vector is empty and false if not
     */
    bool empty()
    {
        return this->size() == 0;
    }

    /**
     * @brief gets the T object in the speified placement
     * @param index the index
     * @return the T object in the right placement
     */
    T at(size_t index) const
    {
        if (index >= 0)
        {
            if (index <= this->_size)
            {
                if (this->_isDynamic)
                {
                    return this->_dataDynamic[index];

                }
                else
                {
                    return this->_dataC[index];
                }
            }
            else
            {
                throw std::out_of_range ("the index is greater than the array size");
            }
        }
        else
        {
            throw std::out_of_range ("the index is negative");
        }
    }

    /**
     * @brief add an item to the back of the vector
     * @param newItem the item to add
     */
    void push_back(T newItem)
    {
        if(this->_size == this->_capacity)
        {
            _createDynamic();
            this->_dataDynamic[this->_size] = newItem;
        }
        else
        {
            if(this->_isDynamic)
            {
                this->_dataDynamic[this->_size] = newItem;
            }
            else
            {
                this->_dataC[this->_size] = newItem;
            }
        }
        this->_size += 1;
    }

    /**
     * @brief inserts an item beforre a position in the vector
     * @param position the iterator pointing to the position
     * @param newItem the item to add
     * @return the iterator pointing to the new item
     */
    Iterator insert(Iterator position, T newItem)
    {
        size_t size = this->size();
        Iterator toReturn(position);
        for(size_t i = 0; i < this->size(); i++)
        {
            if (this->at(i) == *position)
            {
                T* arr;
                arr = new (nothrow)T[this->_size - i];
                for (size_t j = 0; j < this->size() - i; j++)
                {
                    arr[j] = this->at(i + j);
                }
                this->_size = i;
                this->push_back(newItem);
                for (size_t l = 0; l < size - i; l++)
                {
                    this->push_back(arr[l]);
                }
                delete [] arr;
                arr = NULL;
                break;
            }
        }
        return toReturn;
    }

    /**
     * @brief inserts all items between the two iterators to the vector
     * @tparam InputIterator the iterator type
     * @param position the position to insert them
     * @param first the left most object to add
     * @param last the right most object to add
     * @return an iterator pointing to the first object added
     */
    template<class InputIterator>
    Iterator insert(Iterator position, InputIterator first, InputIterator last)
    {
        size_t size = this->size();
        Iterator toReturn(position);
        if(position == end())
        {
            while (first != last)
            {
                this->push_back(*first);
                first++;
            }
        }
        else
        {
            for(size_t i = 0; i < this->size(); i++)
            {
                if(this->at(i) == *position)
                {
                    T* arr;
                    arr = new (nothrow)T[this->_size - i];
                    for (size_t j = 0; j < this->size() - i; j++)
                    {
                        arr[j] = this->at(i + j);
                    }
                    this->_size = i;
                    while (first != last - 1)
                    {
                        this->push_back(*first);
                        first++;
                    }
                    //insert the last item
                    this->push_back(*first);
                    for(size_t l = 0; l < size - i; l++)
                    {
                        this->push_back(arr[l]);
                    }
                    delete [] arr;
                    arr = NULL;
                    break;
                }
            }
        }
        return toReturn;
    }

    /**
     * @brief removes the last object from the vector
     */
    void pop_back()
    {
        if(!this->empty())
        {
            this->_size -= 1;
            _shrink();
        }
    }

    /**
     * @brief erases an item from the vector
     * @param remove an iterator pointing to the item to remove
     * @return an iterator pointing to the item in its place
     */
    Iterator erase(Iterator remove)
    {
        Iterator toReturn(remove);
        Iterator iter2(remove + 1);
        while(iter2 != this->end())
        {
            *remove = *iter2;
            iter2++;
            remove++;
        }
        *remove = *iter2;
        this->_size -= 1;
        _shrink();
        return toReturn;
    }

    /**
     * @brief eraser a range of items
     * @param first the iterator pointing to the leftmost object
     * @param last the iterator pointing to the rightmost object
     * @return an iterator pointing to the item in their place
     */
    Iterator erase(Iterator first, Iterator last)
    {
        size_t counter = 0;
        Iterator saveFirst(first);
        Iterator saveLast(last);
        Iterator toReturn(first);
        while (last != end() - 1 && first != saveLast)
        {
            *first = *last;
            first++;
            last++;
            counter++;
        }
        if (first != saveLast)
        {
            *first = *last;
            counter++;
            this->_size = counter;
        }
        else
        {
            while(last != saveLast)
            {
                *first = *last;
                first++;
                last++;
            }
            this->_size -= counter;
        }
        _shrink();
        return Iterator(data());
    }

    /**
     * @brief clears the vector
     */
    void clear()
    {
        this->_size = 0;
        _shrink();
    }

    /**
     * returns a pointer to the container of the items
     */
    T* data()
    {
        if(this->_isDynamic)
        {
            return this->_dataDynamic;
        }
        else
        {
            return this->_dataC;
        }
    }

    /**
     * updates the  '=' operator
     */
    VLVector<T, C> & operator=(const VLVector<T, C> toCopy)
    {
        if(this == toCopy)
        {
            return *this;
        }
        else
        {
            this->_size = toCopy._size;
            this->_capacity = toCopy._capacity;
            if(toCopy._isDynamic)
            {
                this->_isDynamic = true;
                T* temp;
                temp = new (nothrow)T[toCopy._capacity];
                if (temp != nullptr)
                {
                    delete [] this->_dataDynamic;
                    this->_dataDynamic = NULL;
                    this->_dataDynamic = temp;
                    for (size_t i = 0; i < size(); i++)
                    {
                        this->_dataDynamic[i] = toCopy._dataDynamic[i];
                    }
                }
            }
            else
            {
                this->_isDynamic = false;
                T newData[C];
                this->_dataC = newData;
                for(size_t i = 0; i < this->_size; i++)
                {
                    this->_dataC[i] = toCopy._dataC[i];
                }
            }
        }
        return *this;
    }

    /**
     * updates the  '[]' operator
     */
    T operator[](const int index) const
    {
        if(index > (int) this->_size)
        {
            return this->at(this->_size - 1);
        }
        if (index < 0)
        {
            if(index < - (int) this->_size)
            {
                return this->at(0);
            }
            else
            {
                return this->at(this->_size + index);
            }
        }
        return this->at(index);
    }

    /**
     * updates the  '==' operator
     */
    bool operator==(VLVector<T, C> compare) const
    {
        if(this->_size == compare._size)
        {
            for(size_t i = 0; i < this->_size; i++)
            {
                if(this->at(i) == compare.at(i))
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * updates the  '!=' operator
     */
    bool operator!=(VLVector<T, C> compare) const
    {
        if(this->_size == compare._size)
        {
            for(size_t i = 0; i < this->_size; i++)
            {
                if(this->at(i) == compare[i])
                {
                    continue;
                }
                else
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }

private:
    // the container of the items on the heap
    T* _dataDynamic;
    // the container of the items on the stack
    T _dataC[C];
    // saves the size of the vector
    size_t _size;
    // saves the capacity of the vector
    size_t _capacity;
    // flag to see if the heap is being used
    bool _isDynamic = false;

    /**
     * checks the correct capacity enlargement
     */
    size_t _capacityDynamic(size_t s)
    {
        if(s + 1 <=  C)
        {
            return C;
        }
        else
        {
            return floor((3 * (s + 1)) / 2);
        }
    }

    /**
     * @brief moves the vector back to the stack if possible
     */
    void _shrink()
    {
        if(this->_isDynamic)
        {
            if(size() <= C)
            {
                for(size_t i = 0; i < this->_size; i++)
                {
                    this->_dataC[i] = this->_dataDynamic[i];
                }
                delete [] this->_dataDynamic;
                this->_dataDynamic = NULL;
                this->_isDynamic = false;
                this->_capacity = C;
            }
        }
    }

    /**
     * @brief moves the vector to the heap
     */
    void _createDynamic()
    {
        T* temp;
        size_t cap = _capacityDynamic(this->_size);
        temp = new (nothrow)T[cap];
        if (temp != nullptr)
        {
            if(this->_isDynamic)
            {
                for(size_t i = 0; i < this->_size; i++)
                {
                    temp[i] = this->_dataDynamic[i];
                }
                delete [] this->_dataDynamic;
                this->_dataDynamic = NULL;
            }
            else
            {
                for(size_t i = 0; i < this->_size; i++)
                {
                    temp[i] = this->_dataC[i];
                }
            }
            this->_dataDynamic = temp;
            this->_capacity = cap;
            this->_isDynamic = true;
        }
    }
};

#endif //EXAM_VLVECTOR_HPP