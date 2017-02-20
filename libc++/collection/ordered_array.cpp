#include <ordered_array>

#include <cstring>
#include <memory>


ordered_array::ordered_array(uint32_t maxSize, fctLessThan lessThan)
  : _array((void**)kmalloc(maxSize * sizeof(type_t))) // TODO: Test, Might create issues, used to be a void*
  , _size(0)
  , _maxSize(maxSize)
  , _lessThan(lessThan)
{
  memset(_array, 0, maxSize * sizeof(type_t));
}

ordered_array::ordered_array(void *addr, uint32_t maxSize, fctLessThan lessThan)
  : _array((type_t*)addr)
  , _size(0)
  , _maxSize(maxSize)
  , _lessThan(lessThan)
{
  memset(_array, 0, maxSize * sizeof(type_t));
}

/*
ordered_array ordered_array::create(uint32_t maxSize, fctLessThan lessThan)
{
  ordered_array newArray;
  newArray._array = (void*)kmalloc(maxSize * sizeof(type_t));
  memset(newArray._array, 0, maxSize * sizeof(type_t));
  newArray._size = 0;
  newArray._maxSize = maxSize;
  newArray._lessThan = lessThan;
  return newArray;
}

ordered_array ordered_array::place(void *addr, uint32_t maxSize, fctLessThan lessThan)
{
  ordered_array newArray;
  newArray._array = (type_t*)addr;
  memset(newArray._array, 0, maxSize * sizeof(type_t));
  newArray._size = 0;
  newArray._maxSize = maxSize;
  newArray._lessThan = lessThan;
  return newArray;
}
*/

ordered_array::~ordered_array()
{
   // kfree(_array->array);
}

void ordered_array::insert(type_t item)
{
  // ASSERT(array->lessThan);
   uint32_t iterator = 0;
   while (iterator < _size && _lessThan(_array[iterator], item))
       ++iterator;
   if (iterator == _size) // just add at the end of the array.
       _array[_size++] = item;
   else
   {
       type_t tmp = _array[iterator];
       _array[iterator] = item;
       while (iterator < _size)
       {
           iterator++;
           type_t tmp2 = _array[iterator];
           _array[iterator] = tmp;
           tmp = tmp2;
       }
       ++_size;
   }
}

type_t ordered_array::lookup(uint32_t i)
{
  // ASSERT(i < _array->_size);
   return _array[i];
}

void ordered_array::erase(uint32_t i)
{
  while (i < _size)
  {
     _array[i] = _array[i + 1];
     ++i;
  }
  --_size;
}
