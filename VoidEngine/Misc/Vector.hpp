#pragma once

#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    /**
     *  Simple Vector wrapper,
     *  since the standard one doesn't meet my requirements till C++20.
     */
    template<typename T>
    class Vector {
    public:
        /**
         *  Inherited constructors.
         */
        Vector() {}
        ~Vector() = default;

        /**
         *  Initialize with data.
         */
        Vector(std::vector<T> v)
            : m_Data(v) {}
        
        Vector(std::initializer_list<T> il) {
            Append(il);
        }

        /**
         *  Returns whether the dataset is empty.
         */
        bool Empty() const {
            return m_Data.empty();
        }

        /**
         *  Returns the length/size of the dataset.
         */
        u32  Length() const {
            return m_Data.size();
        }

        /**
         *  Check whether an element is contained inside the dataset.
         */
        bool Contains(const T elem) const {
            return FindIndex(elem) != -1;
        }

        /**
         *  Return the index of a given element, or -1 if it doesn't exist in the dataset.
         */
        i32  FindIndex(const T elem) const {
            for(u32 i = 0; i < this->Length(); i++) {
                if(m_Data[i] == elem) { return i; }
            }
            return -1;
        }

        /**
         *  Clear the dataset.
         */
        void Clear() {
            m_Data.clear();
        } 

        /**
         *  Return the raw pointer to the data.
         */
        const T *GetData() const {
            return m_Data.data();
        }

        /**
         *  Prepend element to the start of the dataset.
         */
        void Prepend(const T elem) {
            m_Data.insert(m_Data.begin(), elem);
        }

        /**
         *  Prepend initializer list of elements to the start of the dataset.
         */
        void Prepend(std::initializer_list<T> il) {
            m_Data.insert(m_Data.begin(), il);
        }

        /**
         *  Append element to the dataset.
         */
        void Append(const T elem) {
            m_Data.push_back(elem);
        }

        /**
         *  Append initializer list of elements to the dataset.
         */
        void Append(std::initializer_list<T> il) {
            for(const T t : il) {
                Append(t);
            }
        }

        /**
         *  Remove element via index.
         */
        void Erase(i32 i) {
            if(i >= Length()) { return; }
            m_Data.erase(m_Data.begin() + i);
        }

        /**
         *  Remove element via reference.
         */
        void Remove(const T elem) {
            i32 i = FindIndex(elem);
            if(i != -1) {
                Erase(i);
            }
        }

        /**
         *  Iterator methods.
         */
        typename std::vector<T>::iterator begin() { return m_Data.begin(); }
        typename std::vector<T>::iterator end() { return m_Data.end(); }

        /**
         *  Constant iterator methods.
         */
        const inline typename std::vector<T>::iterator cbegin() const { return m_Data.cbegin(); }
        const inline typename std::vector<T>::iterator cend() const { return m_Data.cend(); }

        /**
         *  Indexing operators.
         */
        T operator [] (i32 pos) { return m_Data[pos]; }
        const T operator [] (i32 pos) const { return m_Data[pos]; }

        /**
         *  Conversion operator to std::vector
         */
        operator std::vector<T> () { return m_Data; }

    protected:
        std::vector<T> m_Data;
    };
};
