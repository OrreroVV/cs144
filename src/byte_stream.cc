#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buf(), pushBytes(0), popBytes(0), is_error(false),  is_close(false){}

bool Writer::is_closed() const
{
  return is_close;
}

void Writer::push( string data )
{
  for (auto& i : data) {
    if (available_capacity() > 0) {
      buf.push(i);
      pushBytes++;
    }
  }
}

void Writer::close()
{
  is_close = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - (pushBytes - popBytes);
}

uint64_t Writer::bytes_pushed() const
{
  return pushBytes;
}

bool Reader::is_finished() const
{
  return (bytes_buffered() == 0 && is_close);
}

uint64_t Reader::bytes_popped() const
{
  return popBytes;
}

string_view Reader::peek() const
{
  return string_view(&buf.front(), 1);
}

void Reader::pop( uint64_t len )
{
  while (len--) {
    buf.pop();
    popBytes++;
  }
}

uint64_t Reader::bytes_buffered() const
{
  return pushBytes - popBytes;
}
