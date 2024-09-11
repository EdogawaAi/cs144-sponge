#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
: buffer(), _capacity(capacity), _read_cnt(0), _write_cnt(0) {
    // DUMMY_CODE(capacity);
}

size_t ByteStream::write(const string &data) {
    // DUMMY_CODE(data);
    // return {};
    if (input_ended()) {
        return 0;
    }
    auto result = min(data.size(), remaining_capacity());
    for (size_t i = 0; i < result; i++) {
        buffer.push_back(data[i]);
    }
    _write_cnt += result;
    return result;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    // DUMMY_CODE(len);
    // return {};
    size_t pop_size = min(len, buffer_size());
    return string(buffer.begin(), buffer.begin() + pop_size);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    // DUMMY_CODE(len)
    //注意，此处更新，而不能在read里更新_read_cnt
    _read_cnt += min(len, buffer_size());
    size_t pop_size = min(buffer_size(), len);
    for (size_t i = 0; i < pop_size; i++) {
        buffer.pop_front();
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    // DUMMY_CODE(len);
    // return {};
    string data = peek_output(len);
    this->pop_output(len);
    return data;
}

void ByteStream::end_input() {
    _input_end = true;
}

bool ByteStream::input_ended() const {
    return _input_end;
}

size_t ByteStream::buffer_size() const {
    return buffer.size();
}

bool ByteStream::buffer_empty() const {
    return buffer.empty();
}

bool ByteStream::eof() const {
    // if buffer is empty
    return this->buffer_empty() && input_ended();
}

size_t ByteStream::bytes_written() const {
    return _write_cnt;
}

size_t ByteStream::bytes_read() const {
    // return {};
    return _read_cnt;
}

size_t ByteStream::remaining_capacity() const {
    // return {};
    return _capacity - buffer_size();
}
