/*****************************************************************************************
 *                                                                                       *
 * GHOUL                                                                                 *
 * General Helpful Open Utility Library                                                  *
 *                                                                                       *
 * Copyright (c) 2012-2015                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <ghoul/misc/assert.h>
#include <typeinfo>

namespace ghoul {

/**
 * This class implements the singleton design pattern.
 * @code
 * class Example: public Singleton<Example> {
 * public:
 *     Example(int n) {...}
 *     void exfunc() {};
 * }
 * int main() {
 *     Example::initialize(2);
 *     Example::ref().exfunc();
 *     Example::deinitialize();
 *     return 0;
 * }
 * @endcode
 */
template <class T>
class Singleton {
public:

	/**
     * Creates and initializes an empty singleton with the arguments passed to the 
	 * template class T constructor.
     * Calling #initialize when the singleton is already initialized will trigger an
     * assertion.
     */
    template <typename... Args>
    static void initialize(Args... args) {
        ghoul_assert( ! isInitialized(), typeid(T).name() << " is already initialized!");
        _instance = new T(std::forward<Args>(args)...);
    }
    
	/**
     * Deinitializes and deletes the singleton. Calling this with an uninitialized
     * singleton will trigger an assertion.
     */
	static void deinitialize() {
		ghoul_assert(isInitialized(), typeid(T).name() << " is not initialized!");
        delete _instance;
        _instance = nullptr;
    }
    
	/**
     * Returns the initialization state of the singleton.
     * \return The initialization state of the singleton
     */
    static bool isInitialized() {
        return (_instance != nullptr);
    }
    
	/**
     * Returns the reference to the singleton. Triggers an assertion if the
     * singleton has not been initialized yet.
     * \return A reference to the singleton
     */
	static T& ref() {
		ghoul_assert(isInitialized(), typeid(T).name() << " is not initialized!");
        return *_instance;
    }

protected:
    Singleton() {};
    ~Singleton() {};
    
private:

    // protecting against evil
    Singleton(const Singleton&) = delete;
    Singleton(const Singleton&&) = delete;
    Singleton& operator= (const Singleton& rhs) = delete;
    
    // instance member
    static T* _instance;
    
}; // Singleton

template <class T> T* Singleton<T>::_instance = nullptr;

} // namespace ghoul
#endif