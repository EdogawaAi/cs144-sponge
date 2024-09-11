#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) :
_output(capacity),
_capacity(capacity),
_unassembled_bytes(0),
datas_(capacity, '\0'),
next_index(0),
_stream(),
is_eof(false)
{}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    // DUMMY_CODE(data, index, eof);
    if (index >= next_index + _output.remaining_capacity())
        return;

    if (eof && index + data.size() <= next_index + _output.remaining_capacity())
        is_eof = true;

    if (index + data.size() > next_index) {
        for (size_t i = max(index, next_index);
            i < next_index + _output.remaining_capacity() && i < index + data.size();
            i++) {
            if (_stream.count(i) == 0) {
                if (datas_.capacity() <= i) {
                    datas_.resize(i * 2);
                }
                datas_[i] = data[i - index];
                _stream[i] = true;
                _unassembled_bytes++;
            }
        }

        while (_stream.count(next_index) > 0) {
            _output.write(string(1, datas_[next_index]));
            _stream.erase(next_index);
            next_index++;
            _unassembled_bytes--;
        }
    }
    if (is_eof && empty())
        _output.end_input();

}

size_t StreamReassembler::unassembled_bytes() const {
    return _unassembled_bytes;
}

bool StreamReassembler::empty() const {
    return _unassembled_bytes == 0;
}
