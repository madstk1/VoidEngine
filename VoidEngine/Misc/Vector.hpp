#ifndef VOID_MISC_VECTOR_H__
#define VOID_MISC_VECTOR_H__

#include <vector>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    template<typename T>
    class Vector {
    public:
        Vector() {}
        ~Vector() = default;

        bool Empty() const { return m_Data.empty(); }
        u32  Length() const { return m_Data.size(); }
        bool Contains(const T elem) const { return FindIndex(elem) != -1; }
        i32  FindIndex(const T elem) const {
            for(u32 i = 0; i < this->Length(); i++) {
                if(this[i] == elem) { return i; }
            }
            return -1;
        }

        void Clear() { m_Data.clear(); }

        void Prepend(const T elem) { m_Data.insert(m_Data.begin(), elem); }
        void Prepend(std::initializer_list<T>) {}

        void Append(const T elem) { m_Data.push_back(elem); }
        void Append(std::initializer_list<T>) {}

        void Erase(i32 i) { m_Data.erase(m_Data.begin() + i); }
        void Remove(const T elem) {
            u32 i = FindIndex(elem);
            if(i != -1) {
                Erase(i);
            }
        }

        typename std::vector<T>::iterator begin() { return m_Data.begin(); }
        typename std::vector<T>::iterator end() { return m_Data.end(); }

        const inline typename std::vector<T>::iterator cbegin() const { return m_Data.cbegin(); }
        const inline typename std::vector<T>::iterator cend() const { return m_Data.cend(); }

        T operator [] (i32 pos) { return m_Data[pos]; }
        const T operator [] (i32 pos) const { return m_Data[pos]; }

    protected:
        std::vector<T> m_Data;
    };
};

#endif /* VOID_MISC_VECTOR_H__ */
