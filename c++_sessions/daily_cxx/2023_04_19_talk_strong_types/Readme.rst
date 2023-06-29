Strong types reinforce interfaces by making them more expressive, especially at call site, and less error-prone by forcing the right order of arguments. They can be implemented by the following thin wrapper:

template <typename T, typename Parameter>
class NamedType
{
public:
    explicit NamedType(T const& value) : value_(value) {}
    explicit NamedType(T&& value) : value_(std::move(value)) {}
    T& get() { return value_; }
    T const& get() const {return value_; }
private:
    T value_;
};
that can be used the following way:

using Width = NamedType<double, struct WidthParameter>;
