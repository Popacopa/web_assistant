
#include <iostream>
#include <cstdarg>


class Byte {
public:
    Byte(const uint8_t& nullSig) : _data(nullSig) {}
    Byte() : _data(0b00) {}

    uint8_t& get_data() noexcept {return _data;}

    void set_data(const uint8_t& arg) {_data = arg;}
    
    void setBit(const int count, ...) {
        va_list args;
        va_start(args, count);
        for (int i = 0; i < count; ++i) {
            int pos = va_arg(args, int);
            _data = _data | (1 << pos);
        }
        va_end(args);
    }

    void clearBit(const int count, ...) {
        va_list args;
        va_start(args, count);
        for (int i = 0; i < count; ++i) {
            int pos = va_arg(args, int);
            _data =  _data & ~(1 << pos);
        }
        va_end(args);
    }

    void print() const {
        std::string result;
        for (int i{7}; i >= 0; i--) {
            std::cout << ((_data >> i) & 1);
        }
        std::cout << "\n";
    }

private:
    uint8_t _data;
};