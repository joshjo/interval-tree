#ifndef CONFIG_H
#define CONFIG_H


template <class C>
class ConfigBase {
    public:
        typedef C T;
        static const bool withLeafs = 0;
        static const bool withQueries = 0;
};


template <class C>
class ConfigOnlyLeafs {
    public:
        typedef C T;
        static const bool withLeafs = 1;
        static const bool withQueries = 0;
};


template <class C>
class ConfigWithQueries {
    public:
        typedef C T;
        static const bool withLeafs = 1;
        static const bool withQueries = 1;
};

#endif // CONFIG_H
