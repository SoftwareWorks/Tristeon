#pragma once

template <typename C, typename T>
class RWProperty
{
	friend C;
public:
	typedef T(C::*Getter_t)();
	typedef void (C::*Setter_t)(T);

	RWProperty(C* instance, Getter_t getter, Setter_t setter) : m_instance(instance), m_getter(getter), m_setter(setter) {}

	T get() { return (m_instance->*m_getter)(); }
	operator T() const { return (this->m_instance->*this->m_getter)(); }

	void set(T value) { (m_instance->*m_setter)(value); }
	RWProperty<C, T>& operator=(T value) { (this->m_instance->*this->m_setter)(value); return *this; }

private:
	C* const m_instance;
	const Getter_t m_getter;
	const Setter_t m_setter;
};

template <typename C, typename T>
class RProperty
{
	friend C;
public:
	typedef T(C::*Getter_t)();
	typedef void (C::*Setter_t)(T);

	RProperty(C* instance, Getter_t getter) : m_instance(instance), m_getter(getter) {}

	T get() { return (m_instance->*m_getter)(); }
	operator T() const { return (this->m_instance->*this->m_getter)(); }

private:
	C* const m_instance;
	const Getter_t m_getter;
};

template <typename C, typename T>
class WProperty
{
	friend C;
public:
	typedef T(C::*Getter_t)();
	typedef void (C::*Setter_t)(T);

	WProperty(C* instance, Setter_t setter) : m_instance(instance), m_setter(setter) {}

	void set(T value) { (m_instance->*m_setter)(value); }
	RWProperty<C, T>& operator=(T value) { (this->m_instance->*this->m_setter)(value); return *this; }

private:
	C* const m_instance;
	const Setter_t m_setter;
};

#define Property(CLASS, NAME, TYPE)	RWProperty<CLASS, TYPE> NAME = { this, &CLASS::get_##NAME, &CLASS::set_##NAME }; \
    typedef TYPE property__tmp_type_##NAME;

#define ReadOnlyProperty(CLASS, NAME, TYPE) RProperty<CLASS, TYPE> NAME = { this, &CLASS::get_##NAME }; \
    typedef TYPE property__tmp_type_##NAME;

#define WriteOnlyProperty(CLASS, NAME, TYPE) WProperty<CLASS, TYPE> NAME() = { this, &CLASS::set_##NAME }; \
    typedef TYPE property__tmp_type_##NAME;

#define GetProperty(NAME) property__tmp_type_##NAME get_##NAME()
#define SetProperty(NAME) void set_##NAME(property__tmp_type_##NAME value)
