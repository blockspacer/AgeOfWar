#ifndef AGEOFWAR_IBITSTREAM_HPP
#define AGEOFWAR_IBITSTREAM_HPP

#include <iostream>

template<typename CharType, typename Traits>
class basic_ibitstream : public std::basic_istream<CharType, Traits> {
public:
    typedef CharType char_type;
    typedef typename Traits::int_type int_type;
    typedef typename Traits::pos_type pos_type;
    typedef typename Traits::off_type off_type;
    typedef CharType traits_type;
private:
    std::size_t m_current_bcount;

protected:
    basic_ibitstream(const basic_ibitstream &rhs) = delete;

    basic_ibitstream(basic_ibitstream &&other) : std::basic_istream<CharType, Traits>(other),
                                               m_current_bcount(std::move(other.m_current_bcount)) {}

	std::size_t &current_bcount() {
		return m_current_bcount;
	}

public:
    explicit basic_ibitstream(std::basic_streambuf<CharType, Traits> *sb) : std::basic_istream<CharType, Traits>(sb),
                                                                            m_current_bcount(sizeof(char_type) << 3) {}


public:
	/* Unformatted (bit-friendly) input */
    basic_ibitstream &get(char_type &ch) {
        m_current_bcount = sizeof(char_type) << 3;
        std::basic_istream<CharType, Traits>::get(ch);
        return *this;
    }

    basic_ibitstream &get(char_type *s, std::streamsize count) {
        m_current_bcount = sizeof(char_type) << 3;
        std::basic_istream<CharType, Traits>::get(s, count);
        return *this;
    }

    basic_ibitstream &get(char_type *s, std::streamsize count, char_type delim) {
        m_current_bcount = sizeof(char_type) << 3;
        std::basic_istream<CharType, Traits>::get(s, count, delim);
        return *this;
    }

    basic_ibitstream &get(std::basic_streambuf<CharType, Traits> &strbuf) {
        m_current_bcount = sizeof(char_type) << 3;
        std::basic_istream<CharType, Traits>::get(strbuf);
        return *this;
    }

    basic_ibitstream &get(std::basic_streambuf<CharType, Traits> &strbuf, char_type delim) {
        m_current_bcount = sizeof(char_type) << 3;
        std::basic_istream<CharType, Traits>::get(strbuf, delim);
        return *this;
    }

	/* Unformatted (bit) input */
    int_type get() {
        m_current_bcount = sizeof(char_type) << 3;
        return std::basic_istream<CharType, Traits>::get();
    }

    int_type get(std::size_t count) {
	    count = std::min(sizeof(int_type) << 8, count);
	    std::cout << "get: " << count << " " << current_bcount() << std::endl;
	    int_type result = 0;
	    while (true) {
	    	if (count < current_bcount())
			    return result | (std::basic_istream<CharType, Traits>::peek() >> (current_bcount() -= count) & (1 << count) - 1);
		    else if (count == current_bcount())
			    return result | (get() & ((1 << count) - 1));
		    std::size_t curr_bcount = current_bcount();
		    result |= (get() & (1 << curr_bcount) - 1) << (count -= curr_bcount);
	    }
    }

    basic_ibitstream &get(int_type &i, std::streamsize count = 1) {
        i = get(count);
        return *this;
    }
};

template<typename CharType, typename Traits>
class basic_obitstream : public std::basic_ostream<CharType, Traits> {
public:
    typedef CharType char_type;
    typedef typename Traits::int_type int_type;
    typedef typename Traits::pos_type pos_type;
    typedef typename Traits::off_type off_type;
    typedef CharType traits_type;

private:
    std::size_t m_current_bcount;
    char_type m_buffer;

protected:
    basic_obitstream(basic_obitstream const &rhs) = default;

    basic_obitstream(basic_obitstream &&other) : std::basic_ostream<CharType, Traits>(other),
        m_current_bcount(std::move(other.m_current_bcount)), m_buffer(std::move(other.m_buffer)) {}

    std::size_t &currentch_bcount() {
        return m_current_bcount;
    }

public:
    explicit basic_obitstream(std::basic_streambuf<CharType, Traits> *sb) : std::basic_ostream<CharType, Traits>(sb),
        m_current_bcount(sizeof(char_type) << 3), m_buffer(0) {}

    basic_obitstream &put(char_type ch) {
        m_current_bcount = sizeof(char_type) << 3;
        m_buffer = 0;
        std::basic_ostream<CharType, Traits>::put(ch);
        return *this;
    }

    basic_obitstream &put(int_type ch, std::size_t count) {
    	count = std::min(sizeof(int_type) << 8, count);
        while (0 < count) {
            if (currentch_bcount() < count) {
                m_buffer |= (ch >> (count -= currentch_bcount())) & ((1 << currentch_bcount()) - 1);
                put(m_buffer);
            } else if (count < currentch_bcount()) {
                m_buffer |= (ch & ((1 << count) - 1)) << (currentch_bcount() -= count);
                count = 0;
            } else {
                put(m_buffer | (ch & ((1 << currentch_bcount()) - 1)));
                count = 0;
            }
        }
        return *this;
    }

    basic_obitstream &flush() {
        if (m_current_bcount != sizeof(char_type) << 3)
            put(m_buffer);
        std::basic_ostream<CharType, Traits>::flush();
        return *this;
    }

    std::size_t currentch_bcount() const {
        return m_current_bcount;
    }

    std::ios_base::fmtflags flags() const {
        return std::basic_ostream<CharType, Traits>::flags();
    }

    std::ios_base::fmtflags flags(std::ios_base::fmtflags flags) {
        return std::basic_ostream<CharType, Traits>::flags(flags);
    }
};

typedef basic_ibitstream<char, std::char_traits<char>> ibitstream;
typedef basic_ibitstream<wchar_t, std::char_traits<char>> wibitstream;

typedef basic_obitstream<char, std::char_traits<char>> obitstream;
typedef basic_ibitstream<wchar_t, std::char_traits<char>> wobitstream;

/*
template<typename CharType, typename Traits>
class basic_bitstream : protected std::basic_iostream<CharType, Traits> {

};
*/

#endif