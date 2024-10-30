#ifndef UTILITIES_UNIQUELIST_H
#define UTILITIES_UNIQUELIST_H

#include <algorithm>
#include <map>
#include <vector>

namespace Delynoi {
    template<class T>
    class UniqueList {
    private:
        std::vector<T> list;
        std::map<T, int> map;

    public:
        UniqueList();

        UniqueList(const UniqueList &other);

        int push_back(T &item);

        int force_push_back(T &item);

        int size();

        std::vector<int> push_list(std::vector<T> &_list);

        std::vector<int> push_list(UniqueList &_list);

        void pop_front();

        std::vector<T> getList() const;

        std::vector<T> &getList();

        int indexOf(T elem);

        T &operator[](int i);

        bool operator==(const UniqueList &other);

        bool contains(T elem);

        bool hasCommonElement(UniqueList &other);

        void clear();

        void delete_element(T item);
    };

    template<class T>
    UniqueList<T>::UniqueList() = default;

    template<class T>
    UniqueList<T>::UniqueList(const UniqueList &other) {
        this->list = other.list;
        this->map = other.map;
    }

    template<class T>
    int UniqueList<T>::push_back(T &item) {
        auto it = map.upper_bound(item);

        if (it == map.begin() || (--it)->first < item) {
            map.insert(it, std::make_pair(item, list.size()));
            list.push_back(item);

            return static_cast<int>(list.size()) - 1;
        }
        return it->second;
    }

    template<class T>
    int UniqueList<T>::force_push_back(T &item) {
        list.push_back(item);

        return static_cast<int>(list.size()) - 1;
    }

    template<class T>
    void UniqueList<T>::pop_front() {
        T elem = this->list[0];

        this->list.erase(this->list.begin());
        this->map.erase(elem);
    }

    template<class T>
    int UniqueList<T>::size() {
        return static_cast<int>(list.size());
    }

    template<class T>
    std::vector<T> UniqueList<T>::getList() const {
        return this->list;
    }

    template<class T>
    int UniqueList<T>::indexOf(T elem) {
        return utilities::indexOf(this->list, elem);
    }

    template<class T>
    bool UniqueList<T>::operator==(const UniqueList &other) {
        return this->list == other.getList();
    }

    template<class T>
    T &UniqueList<T>::operator[](int i) {
        return list[i];
    }

    template<class T>
    std::vector<int> UniqueList<T>::push_list(std::vector<T> &_list) {
        std::vector<int> index;

        for (int i = 0; i < _list.size(); i++) {
            index.push_back(this->push_back(_list[i]));
        }

        return index;
    }

    template<class T>
    std::vector<int> UniqueList<T>::push_list(UniqueList &_list) {
        std::vector<int> index;

        for (int i = 0; i < _list.size(); i++) {
            index.push_back(this->push_back(_list[i]));
        }

        return index;
    }

    template<class T>
    bool UniqueList<T>::contains(T elem) {
        auto iter = map.find(elem);
        return iter != map.end();
    }

    template<class T>
    std::vector<T> &UniqueList<T>::getList() {
        return this->list;
    }

    template<class T>
    bool UniqueList<T>::hasCommonElement(UniqueList &other) {
        for (int i = 0; i < other.size(); i++) {
            if (this->contains(other[i])) {
                return true;
            }
        }

        return false;
    }

    template<class T>
    void UniqueList<T>::clear() {
        this->list.clear();
        this->map.clear();
    }

    template<class T>
    void UniqueList<T>::delete_element(T item) {
        if (!this->contains(item)) {
            return;
        }

        auto iter = map.find(item);
        this->list.erase(this->list.begin() + iter->second);
        this->map.clear();

        for (int i = 0; i < this->list.size(); i++) {
            T e = this->list[i];
            map.insert(std::make_pair(e, i));
        }
    }
} // namespace Delynoi

#endif
