//CopyFast metaprogramming type
template <typename T>
struct copy_fast : std::conditional<std::is_trivially_copyable_v<T>, T, const T &>{};
template <typename T>
struct copy_fast_cv : copy_fast<typename std::remove_cvref_t<T>>{};
template <typename T>
using copy_fast_cv_t = typename copy_fast_cv<T>::type;
