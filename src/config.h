#ifndef CONFIG_H
#define CONFIG_H


template <class C>
class ConfigExtra {
    public:
        typedef C T;
        static const bool withLeafs = 0;
        static const bool withQueries = 0;
        static const bool mapQueries = 0;
};


template <class C>
class ConfigOnlyLeafs {
    public:
        typedef C T;
        static const bool withLeafs = 1;
        static const bool withQueries = 0;
        static const bool mapQueries = 0;
};


template <class C>
class ConfigLazy {
    public:
        typedef C T;
        static const bool withLeafs = 1;
        static const bool withQueries = 1;
        static const bool mapQueries = 0;
};

template <class C>
class ConfigEager {
    public:
        typedef C T;
        static const bool withLeafs = 1;
        static const bool withQueries = 1;
        static const bool mapQueries = 1;
};

#endif // CONFIG_H
