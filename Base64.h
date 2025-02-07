#ifndef BASE64_H
#define BASE64_H

#include <vector>//flexible and dynamic but similar to array
#include <string>

//working of base 64 : We use it to encode and decode strings, it transforms bytes to human readable chars
//So basically base64 has a mapping table where characters are mapped to index starting from 0 till 63
// consider the word man it has 3 letters and the ascii values of these are represented in 8 bits and combined we get 24
//bit string now we divide it into 6 bit strings and then turn the obtained string into decimal and then to character based on our mapping table



namespace Base64
{
    std::string base64_encode(const std::string &);//a constant reference to a string
    // a parameter that will be passed to our function here
    //salts
    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";


    std::string EncryptB64(std::string s)
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(7, SALT3);
        s += SALT1;
        s = base64_encode(s);
        s = SALT2 + SALT3 + SALT1;
        s = base64_encode(s);
        s.insert(1, "L");
        s.insert(7, "M");
        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_encode(const std::string &s)
    {
        std::string ret;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F;//63


        for (const auto &c : s)
        {
            val = (val << 8) + c;//val = val*2^8
            bits += 8;
            while(bits >= 0)
            {
                ret.push_back(BASE64_CODES[(val >> bits) & b63]);
                //binary and and right shift
                bits -= 6;
            }
        }

        if (bits > -6)
        {
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
        }
        while(ret.size() % 4)
        {
            ret.push_back('=');
        }
        return ret;
    }

}



#endif // BASE64_H
