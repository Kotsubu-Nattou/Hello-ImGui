///////////////////////////////////////////////////////////////////////////////////////////////
// 【ヘッダオンリー】struct_vec
//
// ・説明
//   テンプレート型VEC2～4構造体（メンバx, y, z, wの内、2～4つを使用する）
//   様々な初期化方法に対応。
//   構造体に対する四則演算と等値演算に対応。
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once



template <typename T>
struct VEC2 {
    // @ フィールド（クラスと違って構造体のデフォルトスコープはpublic）
    T x, y;

    // @ コンストラクタ
    // ＜対応する初期化方法＞
    // VEC2<int> vec;           --- ゼロクリア
    // VEC2<int> vec = {3, 5};  --- 初期値をセット
    // VEC2<int> vec(3, 5);     --- 同上
    // VEC2<int> vec = pos;     --- 同じ型のVEC2を初期値にする
    // VEC2<int> vec(pos);      --- 同上
    VEC2() { this->x = this->y = static_cast<T>(0); }
    VEC2(T vx, T vy) { this->x = vx; this->y = vy; }
    VEC2(const VEC2<T> &v) { this->x = v.x; this->y = v.y; }

    // @ オペレーター
    // ＜対応する演算＞
    // vec = vec + pos;    --- 構造体同士の演算
    // vec = vec * 2 + 1;  --- 各メンバに対する演算
    // vec += pos;         --- 構造体の複合代入演算
    // vec /= 3;           --- 各メンバに対する複合代入演算
    // if (vec == pos)     --- 構造体同士の等値演算
    // if (vec != 0)       --- 各メンバに対する等値演算
    VEC2<T> operator+(const VEC2<T> &v) { return {this->x + v.x, this->y + v.y}; }
    VEC2<T> operator-(const VEC2<T> &v) { return {this->x - v.x, this->y - v.y}; }
    VEC2<T> operator*(const VEC2<T> &v) { return {this->x * v.x, this->y * v.y}; }
    VEC2<T> operator/(const VEC2<T> &v) { return {this->x / v.x, this->y / v.y}; }
    VEC2<T> operator+=(const VEC2<T> &v) { return {this->x += v.x, this->y += v.y}; }
    VEC2<T> operator-=(const VEC2<T> &v) { return {this->x -= v.x, this->y -= v.y}; }
    VEC2<T> operator*=(const VEC2<T> &v) { return {this->x *= v.x, this->y *= v.y}; }
    VEC2<T> operator/=(const VEC2<T> &v) { return {this->x /= v.x, this->y /= v.y}; }
    bool operator==(const VEC2<T> &v) { return this->x == v.x && this->y == v.y; } 
    bool operator!=(const VEC2<T> &v) { return !(*this == v); } 
    VEC2<T> operator+(T val) { return {this->x + val, this->y + val}; }
    VEC2<T> operator-(T val) { return {this->x - val, this->y - val}; }
    VEC2<T> operator*(T val) { return {this->x * val, this->y * val}; }
    VEC2<T> operator/(T val) { return {this->x / val, this->y / val}; }
    VEC2<T> operator+=(T val) { return {this->x += val, this->y += val}; }
    VEC2<T> operator-=(T val) { return {this->x -= val, this->y -= val}; }
    VEC2<T> operator*=(T val) { return {this->x *= val, this->y *= val}; }
    VEC2<T> operator/=(T val) { return {this->x /= val, this->y /= val}; }
    bool operator==(T val) { return this->x == val && this->y == val; }
    bool operator!=(T val) { return !(*this == val); }
};





template <typename T>
struct VEC3 {
    // @ フィールド
    T x, y, z;

    // @ コンストラクタ
    VEC3() { this->x = this->y = this->z = static_cast<T>(0); }
    VEC3(T vx, T vy, T vz) { this->x = vx; this->y = vy; this->z = vz; }
    VEC3(const VEC3<T> &v) { this->x = v.x; this->y = v.y; this->z = v.z; }

    // @ オペレーター
    VEC3<T> operator+( const VEC3<T> &v) { return {this->x + v.x, this->y + v.y, this->z + v.z}; }
    VEC3<T> operator-( const VEC3<T> &v) { return {this->x - v.x, this->y - v.y, this->z - v.z}; }
    VEC3<T> operator*( const VEC3<T> &v) { return {this->x * v.x, this->y * v.y, this->z * v.z}; }
    VEC3<T> operator/( const VEC3<T> &v) { return {this->x / v.x, this->y / v.y, this->z / v.z}; }
    VEC3<T> operator+=(const VEC3<T> &v) { return {this->x += v.x, this->y += v.y, this->z += v.z}; }
    VEC3<T> operator-=(const VEC3<T> &v) { return {this->x -= v.x, this->y -= v.y, this->z -= v.z}; }
    VEC3<T> operator*=(const VEC3<T> &v) { return {this->x *= v.x, this->y *= v.y, this->z *= v.z}; }
    VEC3<T> operator/=(const VEC3<T> &v) { return {this->x /= v.x, this->y /= v.y, this->z /= v.z}; }
    bool    operator==(const VEC3<T> &v) { return this->x == v.x && this->y == v.y && this->z == v.z; } 
    bool    operator!=(const VEC3<T> &v) { return !(*this == v); } 
    VEC3<T> operator+( T val) { return {this->x + val, this->y + val, this->z + val}; }
    VEC3<T> operator-( T val) { return {this->x - val, this->y - val, this->z - val}; }
    VEC3<T> operator*( T val) { return {this->x * val, this->y * val, this->z * val}; }
    VEC3<T> operator/( T val) { return {this->x / val, this->y / val, this->z / val}; }
    VEC3<T> operator+=(T val) { return {this->x += val, this->y += val, this->z += val}; }
    VEC3<T> operator-=(T val) { return {this->x -= val, this->y -= val, this->z -= val}; }
    VEC3<T> operator*=(T val) { return {this->x *= val, this->y *= val, this->z *= val}; }
    VEC3<T> operator/=(T val) { return {this->x /= val, this->y /= val, this->z /= val}; }
    bool    operator==(T val) { return this->x == val && this->y == val && this->z == val; }
    bool    operator!=(T val) { return !(*this == val); }
};





template <typename T>
struct VEC4 {
    // @ フィールド
    T x, y, z, w;

    // @ コンストラクタ
    VEC4() { this->x = this->y = this->z = this->w = static_cast<T>(0); }
    VEC4(T vx, T vy, T vz, T vw) { this->x = vx; this->y = vy; this->z = vz; this->w = vw; }
    VEC4(const VEC4<T> &v) { this->x = v.x; this->y = v.y; this->z = v.z; this->w = v.w; }

    // @ オペレーター
    VEC4<T> operator+( const VEC4<T> &v) { return {this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w}; }
    VEC4<T> operator-( const VEC4<T> &v) { return {this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w}; }
    VEC4<T> operator*( const VEC4<T> &v) { return {this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w}; }
    VEC4<T> operator/( const VEC4<T> &v) { return {this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w}; }
    VEC4<T> operator+=(const VEC4<T> &v) { return {this->x += v.x, this->y += v.y, this->z += v.z, this->w += v.w}; }
    VEC4<T> operator-=(const VEC4<T> &v) { return {this->x -= v.x, this->y -= v.y, this->z -= v.z, this->w -= v.w}; }
    VEC4<T> operator*=(const VEC4<T> &v) { return {this->x *= v.x, this->y *= v.y, this->z *= v.z, this->w *= v.w}; }
    VEC4<T> operator/=(const VEC4<T> &v) { return {this->x /= v.x, this->y /= v.y, this->z /= v.z, this->w /= v.w}; }
    bool    operator==(const VEC4<T> &v) { return this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w; } 
    bool    operator!=(const VEC4<T> &v) { return !(*this == v); } 
    VEC4<T> operator+( T val) { return {this->x + val, this->y + val, this->z + val, this->w + val}; }
    VEC4<T> operator-( T val) { return {this->x - val, this->y - val, this->z - val, this->w - val}; }
    VEC4<T> operator*( T val) { return {this->x * val, this->y * val, this->z * val, this->w * val}; }
    VEC4<T> operator/( T val) { return {this->x / val, this->y / val, this->z / val, this->w / val}; }
    VEC4<T> operator+=(T val) { return {this->x += val, this->y += val, this->z += val, this->w += val}; }
    VEC4<T> operator-=(T val) { return {this->x -= val, this->y -= val, this->z -= val, this->w -= val}; }
    VEC4<T> operator*=(T val) { return {this->x *= val, this->y *= val, this->z *= val, this->w *= val}; }
    VEC4<T> operator/=(T val) { return {this->x /= val, this->y /= val, this->z /= val, this->w /= val}; }
    bool    operator==(T val) { return this->x == val && this->y == val && this->z == val && this->w == val; }
    bool    operator!=(T val) { return !(*this == val); }
};
