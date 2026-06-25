#pragma once

#include <stdexcept>
#include <vector>

template<class T>
class puyoForwardVector
{
    private :
        size_t left_ptr, right_ptr;
        std::vector<T> vec;
        const int pointer_count;

        inline size_t relative_index(size_t idx) const {return idx-left_ptr;}
        
    public :
        puyoForwardVector(int pointer_count = 2)
            : right_ptr(0), left_ptr(0)
            , vec(std::vector<T>())
            , pointer_count(0 < pointer_count && pointer_count <= 2
                            ? pointer_count
                            : throw std::runtime_error("pointer_count of puyoForwardVector is not between 0 and 2"))
        {}

        inline bool accessable(size_t idx) const {return idx >= left_ptr && relative_index(idx) < vec.size();}

        T toss(size_t idx)
        {
            if(!accessable(idx))
                throw std::runtime_error("out of ranges of puyoForwardVector");

            const size_t new_ptr = relative_index(idx);
            if(pointer_count == 1)
            {
                ++right_ptr;
                ++left_ptr;
                T element = std::move(vec[new_ptr]);
                vec.erase(vec.begin());
                return element;
            }

            if(idx == right_ptr)
            {
                ++right_ptr;
                return vec[new_ptr];
            }
            else if(idx == left_ptr)
            {
                ++left_ptr;
                T element = std::move(vec[new_ptr]);
                vec.erase(vec.begin());
                return element;
            }
            throw std::runtime_error("tossing between range of puyoForwardVector is not allowed");
        }
        inline T operator[](size_t idx) {return toss(idx);}

        const T& view(size_t idx) const
        {
            if(!accessable(idx))
                throw std::runtime_error("out of ranges of puyoForwardVector");
            return vec[relative_index(idx)];
        }
        inline T& refer(size_t idx)
        {
            if(!accessable(idx))
                throw std::runtime_error("out of ranges of puyoForwardVector");
            return vec[relative_index(idx)];
        }
        inline T& front() {return vec.front();}
        inline T& back() {return vec.back();}
        
        inline void push_back(const T& element) {vec.push_back(element);}
        inline void push_back(T&& element) {vec.push_back(std::move(element));}

        inline bool empty() const {return vec.empty();}

        inline void clear()
        {
            left_ptr = 0;
            right_ptr = 0;
            vec.clear();
        }

        inline size_t size() const {return vec.size();}
        inline size_t get_start_point() const {return left_ptr;}
        inline size_t get_end_point() const {return right_ptr;}
};