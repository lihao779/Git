#pragma once

#include <assert.h>
#include <vector>
using namespace std;
namespace bite
{
    template<size_t N>
    class bitset
    {
        public:
            bitset()
                :_bst(N/8+1)
            {}
            void set(unsigned long date)
            {
                assert(date < N);
                //计算date是那个字节
                size_t whichByte = date/8;
                //计算date是那个比特位
                size_t whichBit = date%8;
                
                _bst[whichByte] |= (1 << whichBit);

            }
            void reset(unsigned long date)
            {
                assert(date < N);
                //计算date是那个字节
                size_t whichByte = date/8;
                //计算date是那个比特位
                size_t whichBit = date%8;

                _bst[whichByte] &= ~(1 << whichBit);

            }
            bool test(unsigned long date)
            {
                assert(date < N);
                //计算date是那个字节
                size_t whichByte = date/8;
                //计算date是那个比特位
                size_t whichBit = date%8;
                
                return _bst[whichByte] & (1 << whichBit);


            }
            size_t count()const 
            {
                int bitCnttable[256] = {
                    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
                    3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
                    3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
                    4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
                    3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
                    6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
                    4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
                    6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
                    3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
                    4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
                    6, 7, 6, 7, 7, 8
                };
                size_t count = 0;
                for(int i = 0;i<_bst.size();i++)
                {
                    count += bitCnttable[_bst[i]];
                }
                return count;
            }
            size_t size()const
            {
                return N;
            }
        private:
        vector<unsigned char> _bst;    
    };
}
