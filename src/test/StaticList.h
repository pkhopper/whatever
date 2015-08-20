// a static list, use a block of memory (or shm), easy to be serialized
#ifndef __STATIC_LIST__
#define __STATIC_LIST__

namespace test
{
    template<class Data_t>
    struct StaticListNode
    {
        int next;
        int pre;
        Data_t self;
    };

    template<class Data_t, size_t ElementCount>
    class StaticList
    {
    public:
        struct _Node
        {
            int next;
            int pre;
            Data_t self;
        };
        struct _IdelList 
        {
            _IdelList() : count(ElementCount), first(0) {}
            size_t count;
            int first;
        } idel_;
        struct _UsedList 
        {
            _UsedList() : count(0), first(-1), last(-1) {}
            size_t count;
            int first;
            int last;
        } used_;

        void push_back(const Data_t& _Val)
        {
            if (idel_.count == 0)
            {
                // ???
                return;
            }
            idel_.count--;
            used_.count++;
            auto &first = data_[idel_.first];
            if (first->next == 0 && first->pre == 0)
            {
                idel_.first = 
            }
            data_[idel_.first].next = -1;
            data_[idel_.first].pre = used_.last;
            data_[used_.last].next = idel_.first;
        }
        
    protected:
        int    size_;
        size_t count_;
        _Node  data_[ElementCount];
    };

}


#endif
