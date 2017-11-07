#ifndef NYA_HPP
#define	NYA_HPP

// Try to include this file to the last of all includes,
// because of some necessary #defines.

// #include <limits>
#define qnan std::numeric_limits<double>::quiet_NaN()
#define infin std::numeric_limits<double>::infinity()

// #include <unordered_map>
#define umap std::unordered_map

// #include <unordered_set>
#define uset std::unordered_set

// #include <memory>
#define u_p std::unique_ptr
#define s_p std::shared_ptr
#define w_p std::weak_ptr
#define sp_cast std::static_pointer_cast
#define dp_cast std::dynamic_pointer_cast
#define make_p std::make_pair
#define make_s std::make_shared
#define make_u std::make_unique

// common aliases
#define all(x) (x).begin(), (x).end()

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef long long llong;
typedef unsigned long long ullong;

#define NYA_DT_FORMAT "yyyy-MM-dd hh:mm:ss"
#define NYA_DATE_FORMAT "yyyy-MM-dd"

#endif	/* NYA_HPP */

