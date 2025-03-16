#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Object" << std::endl;
	delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Array" << std::endl;
	delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void (T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
	ObjectType* m_object;
	int* m_ref_counter;

	// ======= ADD CODE HERE IF NEEDED =========
				
public:
	////////////////////////////////////////////
	// Constructors 

	SharedPtr(ObjectType* object = nullptr) {
		m_object = object; 
		m_ref_counter = nullptr;
		if (m_object != nullptr) {
			m_ref_counter = new int; 
			*m_ref_counter = 1; 
		}
	}
	SharedPtr(const SharedPtr <ObjectType, Dealloc>& other) {
		m_object = other.m_object; 
		m_ref_counter = other.m_ref_counter; 
		if (m_ref_counter != nullptr) {
			(*m_ref_counter)++; 
		}
	}

	// Destructor
	
	~SharedPtr() {
		if (m_ref_counter != nullptr && --(*m_ref_counter) == 0) {
			Dealloc(m_object);
			delete m_ref_counter;
		}
	}
	
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Assignment operator
	
	SharedPtr& operator=(const SharedPtr& other) {
		if (this != &other) { // this is a pointer left to '=' and other is a pointer right to '='
			if (m_ref_counter != nullptr && --(*m_ref_counter) == 0) {
				Dealloc(m_object); 
				delete m_ref_counter; 
			}
			m_object = other.m_object; 
			m_ref_counter = other.m_ref_counter; 
			if (m_ref_counter != nullptr) {
				++(*m_ref_counter); 
			}
		}
		return *this; 
	}
	
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	
	ObjectType* operator -> () {
		return m_object;
	}
	
	const ObjectType* operator -> () const {
		return m_object; 
	}

	
	// operator*

	ObjectType& operator*() {
		return *m_object;
	}

	const ObjectType& operator * () const {
		return *m_object; 
	}

	// ======= ADD CODE HERE IF NEEDED =========
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]

	ObjectType& operator[] (int index) {
		return m_object[index]; 
	}

	const ObjectType& operator[] (int index) const {
		return m_object[index];
	}
	
	// ======= ADD CODE HERE IF NEEDED =========

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]                                         이거 반복되는거 아님? 위에꺼랑?? 
	
	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	
	operator ObjectType const* () const {
		return m_object; 
	}

	// operator ObjectType*()

	operator ObjectType* () {
		return m_object; 
	}
	
	// ======= ADD CODE HERE IF NEEDED =========
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
