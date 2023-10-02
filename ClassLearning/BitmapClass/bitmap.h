#pragma once
typedef long long int int64;


class bitmap
{
public:
    bitmap();
    bitmap(int num_bits);
    ~bitmap();

    int get(int index) const;
    void set(int index, int value);

protected:
    int64 * data;
    int num_bits;

private:
    /**
     * \brief Bits in the size of the int64 type.
     */
    const int bits_per_int64 = sizeof(int64) * 8;
};
