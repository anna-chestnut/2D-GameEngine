#pragma once

#include <assert.h>
#include <cstddef>
#include <stdint.h>

namespace Engine {

	typedef uint64_t	ref_counter_t;

	struct ReferenceCounters
	{

		ReferenceCounters(ref_counter_t i_InitialSmartReferences, ref_counter_t i_InitialWeakReferences) :
			m_SmartReferences(i_InitialSmartReferences),
			m_WeakReferences(i_InitialWeakReferences)
		{}

		ref_counter_t SmartRefs() const { return m_SmartReferences; }
		ref_counter_t IncSmartRefs() { return ++m_SmartReferences; }
		ref_counter_t DecSmartRefs() { return --m_SmartReferences; }

		ref_counter_t WeakRefs() const { return m_WeakReferences; }
		ref_counter_t IncWeakRefs() { return ++m_WeakReferences; }
		ref_counter_t DecWeakRefs() { return --m_WeakReferences; }
	private:
		ref_counter_t		m_SmartReferences;
		ref_counter_t		m_WeakReferences;
	};

	template<class T>
	class WeakPtr;

	template<class T>
	class SmartPtr
	{
		// friends of another (derived) type
		template<class U>
		friend class WeakPtr;

		template<class U>
		friend class SmartPtr;

	public:
		// constructs empty Smartptr.
		// operator==() and operator bool() will return false;
		SmartPtr() :
			pCounters(nullptr),
			pPtr(nullptr)
		{}

		//
		explicit SmartPtr(T* i_ptr) :
			pCounters(i_ptr ? new ReferenceCounters(1, 0) : nullptr),
			pPtr(i_ptr)
		{}

		// Copy Constructor from SmartPtr to same type
		SmartPtr(const SmartPtr& i_other) :
			pPtr(i_other.pPtr),
			pCounters(i_other.pCounters)
		{
			pCounters->IncSmartRefs();
		}

		explicit SmartPtr(T* i_ptr, ReferenceCounters* counters) {
			pPtr = i_ptr;
			pCounters = counters;
			if (pCounters) pCounters->IncSmartRefs();
		}
		// Copy Constructor from SmartPtr to derived type
		/*template<class U>
		SmartPtr(const SmartPtr<U>& i_other) :
			pPtr(i_other.pPtr),
			pCounters(i_other.pCounters)
		{
			pCounters->IncSmartRefs();
		}*/

		// Move Copy Constructor from SmartPtr of same type
		//SmartPtr(const SmartPtr&& i_other) :
		//	pPtr(i_other.pPtr),
		//	pCounters(i_other.pCounters)
		//{
		//	pCounters->IncSmartRefs();
		//	//i_other.pPtr = nullptr;
		//	//i_other.pCounters = nullptr;
		//}

	
		// Copy Constructor from WeakPtr of same type
		SmartPtr(const WeakPtr<T>& i_other) : //SmartPtr(const WeakPtr, DestroyT>& i_other) ?
			pPtr(i_other.pPtr),
			pCounters(i_other.pCounters)
		{
			assert(pCounters->SmartRefs() > 0);
			pCounters->IncSmartRefs();
		}

		// Assignment Operators
		SmartPtr& operator=(const SmartPtr& i_other)
		{
			if (pCounters) {
				pCounters->DecSmartRefs();
				if (pCounters->SmartRefs() == 0)
					delete pCounters;
			}

			pPtr = i_other.pPtr;
			pCounters = i_other.pCounters;
			pCounters->IncSmartRefs();
			return *this;
		}

		// Move Assignment Operators
		SmartPtr& operator=(SmartPtr&& i_other) {
			
			if (pCounters) {
				pCounters->DecSmartRefs();
				if (pCounters->SmartRefs() == 0)
					delete pCounters;
			}
			pPtr = i_other.pPtr;
			pCounters = i_other.pCounters;
			pCounters->IncSmartRefs();

			return *this;
		}
		/*template<class U>
		SmartPtr& operator=(SmartPtr<U>&& i_other);*/

		// Assignment Operator - null specific - easier implementation
		SmartPtr& operator=(std::nullptr_t i_null) {
			pCounters->DecSmartRefs();

			if (pCounters->SmartRefs() == 0)
			{
				delete pPtr;

				if (pCounters->WeakRefs() == 0)
					delete pCounters;
			}
		}

		// Destructor
		~SmartPtr() {

			pCounters->DecSmartRefs();

			if (pCounters->SmartRefs() == 0)
			{
				delete pPtr;

				if (pCounters->WeakRefs() == 0)
					delete pCounters;
			}


		}

		// Equality operators
		bool operator==(const SmartPtr& i_other) const {
			return pPtr == i_other.pPtr;
		}
		/*template<class U>
		bool operator==(const SmartPtr<U>& i_other) const {
			return pPtr == i_other.pPtr;
		}*/

		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		bool operator==(const WeakPtr<T>& i_other) const {

			if (pCounters->m_WeakReferences == 0) return false;
			return pPtr == i_other.pPtr;
		}

		/*template<class U>
		bool operator==(const WeakPtr<U>& i_other) const {
			if (pCounters->m_WeakReferences == 0) return false;
			return pPtr == i_other.pPtr;
		}

		template<class U>
		bool operator==(U* i_ptr) const;*/

		bool operator==(std::nullptr_t nullp) const;

		// Inequality opertors
		bool operator!=(const SmartPtr& i_other) const {
			return pPtr != i_other.pPtr;
		}
		/*template<class U>
		bool operator!=(const SmartPtr<U>& i_other) const;*/

		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		bool operator!=(const WeakPtr<T>& i_other) const {
			if (pCounters->m_WeakReferences == 0) return true;
			return pPtr != i_other.pPtr;
		}

		/*template<class U>
		bool operator!=(const WeakPtr<U>& i_other) const {
			if (pCounters->m_WeakReferences == 0) return true;
			return pPtr != i_other.pPtr;
		}*/


		// bool operator - used for using inside if() checks to see if it's a valid SmartPtr (underlying object hasn't been released)
		inline operator bool() const {
			return pCounters->SmartRefs() > 0 && pPtr != nullptr;
		}

		// Access operator
		T* operator->() {
			return pPtr;
		}

		T& operator*() {
			assert(pPtr);
			return *pPtr;
		}

		// Access operator for const types
		const T* operator->() const {
			return pPtr;
		}

		const T& operator*() const {
			assert(pPtr);
			return *pPtr;
		}

	private:
		ReferenceCounters *		pCounters;
		T *						pPtr;
	};

	template<class T>
	class WeakPtr
	{
		template<class U>
		friend class SmartPtr;
		template<class U>
		friend class WeakPtr;

	public:
		WeakPtr() :
			pCounters(nullptr),
			pPtr(nullptr)
		{}

		// Constructor from SmartPtrs
		WeakPtr(const SmartPtr<T>& i_owner) :
			pPtr(i_owner.pPtr),
			pCounters(i_owner.pCounters)
		{
			pCounters->IncWeakRefs();
		}

		/*template<class U>
		WeakPtr(const SmartPtr<U>& i_owner) :
			pPtr(i_owner.pPtr),
			pCounters(i_owner.pCounters)
		{
			pCounters->IncWeakRefs;
		}*/

		// Constructor from WeakPtrs
		WeakPtr(const WeakPtr& i_owner) :
			pPtr(i_owner.pPtr),
			pCounters(i_owner.pCounters)
		{
			pCounters->IncWeakRefs();
		}

		/*template<class U>
		WeakPtr(const WeakPtr<U>& i_owner) :
			pPtr(i_owner.pPtr),
			pCounters(i_owner.pCounters)
		{
			pCounters->IncWeakRefs;
		}*/

		// Destructor
		~WeakPtr() {
			pCounters->DecWeakRefs();

			if (pCounters->WeakRefs() == 0 && pCounters->SmartRefs() == 0)
				delete pCounters;
		}

		// Assignment operators
		WeakPtr& operator=(const WeakPtr& i_other) 
		{
			pPtr = i_other.pPtr;
			pCounters = i_other.pCounters;
			return *this;
		}

		/*template<class U>
		WeakPtr& operator=(const WeakPtr<U>& i_other)
		{
			pPtr = i_other.pPtr;
			pCounters = i_other.pCounters;
			return *this;
		}*/

		WeakPtr& operator=(const SmartPtr<T>& i_other) 
		{
			pPtr = i_other.pPtr;
			pCounters = i_other.pCounters;
			return *this;
		}

		/*template<class U>
		WeakPtr& operator=(const SmartPtr<U>& i_other) 
		{
			pPtr = i_other.pPtr;
			pCounters = i_other.pCounters;
			return *this;
		}*/

		// null specific version - easier implmentation
		WeakPtr<T>& operator=(std::nullptr_t i_null) {
			pCounters->DecWeakRefs();

			if (pCounters->WeakRefs() == 0 && pCounters->SmartRefs() == 0)
				delete pCounters;
		}

		// Attempt to acquire a SmartPtr (Owner)
		// Just calls the Copy Construct SmartPtr(const WeakPtr, DestroyT>& i_other)
		// which should verify if the underlying object is valid and set itself
		// into the appropriate state (valid underlying pointer or empty (pPtr is null)
		inline SmartPtr<T> AcquireOwnership() {
			return SmartPtr<T>(this->pPtr, this->pCounters);
		}

		inline bool operator==(const WeakPtr& i_other)
		{
			return pPtr == i_other.pPtr;
		}

		/*template<class U>
		inline bool operator==(const WeakPtr<U>& i_other)
		{
			return pPtr == i_other.pPtr;
		}*/

		// Comparison operators
		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		inline bool operator==(const SmartPtr<T>& i_other)
		{
			return pPtr == i_other.pPtr;
		}

		/*template<class U>
		inline bool operator==(const SmartPtr<U>& i_other)
		{
			return pPtr == i_other.pPtr;
		}*/

		inline bool operator==(T* i_ptr) {
			return pPtr == i_ptr;
		}

		// Be careful with the implementations here. The WeakPtr may have a
		// non-null pointer but the object may have been released we need to
		// check the Owner count before comparing the pointers.
		inline bool operator!=(const SmartPtr<T>& i_other)
		{
			if (pCounters->m_SmartReferences == 0)return false;
			return pPtr != i_other.pPtr;
		}

		/*template<class U>
		inline bool operator!=(const SmartPtr<U>& i_other)
		{
			if (pCounters->m_SmartReferences == 0)return false;
			return pPtr != i_other.pPtr;
		}

		template<class U>
		inline bool operator!=(const WeakPtr<U, DestroyU>& i_other);*/


		operator bool() const 
		{
			return pCounters->m_SmartReferences > 0 && pPtr != nullptr;
		}

		T* GetPtr() {
			return pPtr;
		}

	private:
		ReferenceCounters* pCounters;
		T* pPtr;
	};

} // namespace Engine