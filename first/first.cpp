#include <bitset>
#include <iostream>

using namespace std;

template <size_t nomen_Size>
class Generator {
private:
    bitset<nomen_Size> nomen_;
    bitset<nomen_Size - 1> IV_;

public:
    Generator(const bitset<nomen_Size>& nomen_, const bitset<nomen_Size - 1>& IV_)
        : nomen_(nomen_), IV_(IV_) {}

    bool iterate() {
        const bool cOut = IV_.test(0);
        bool c = IV_.test(0);

        for (size_t i = 1; i < nomen_.size() - 1; i++) {
            c ^= IV_.test(i) & nomen_.test(i);
        }

        IV_ >>= 1;
        if (c)
            IV_.set(nomen_Size - 2);

        return cOut;
    }

    bitset<nomen_Size - 1> getIV_() const {
        return IV_;
    }
};

int main() {
    bitset<6> nomen_("100101");
    bitset<5> IV_(25);

    bitset<32> output;

    Generator<6> generator(nomen_, IV_);

    for (int j = 0; j < 32; j++) {
        cout << "[" << j << "]: " << generator.getIV_() << " | ";
        if (generator.iterate())
            output.set(j);

        cout << output[j] << endl;
    }

    cout << output << endl;
    return 0;
}
