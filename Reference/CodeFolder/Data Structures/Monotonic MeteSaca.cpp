struct mono_stack
{
    vector<pair<int,int>> st;

    void push(int v, int idx)
    {
        // cambiar <= a < si quieres ser estricto
        while (!st.empty() && st.back().first <= v)
            st.pop_back();
        st.emplace_back(v, idx);
    }

    void pop()
    {
        if (!st.empty())
            st.pop_back();
    }

    int top() const // verificar primero empty()!!!
    {
        return st.back().first;
    }

    bool empty() const { return st.empty(); }
    size_t size() const { return st.size(); }
};

struct mono_queue
{
    deque<pair<int,int>> dq; // {valor, idx}

    void push(int v, int idx)
    {
        // cambiar <= a < si quieres ser estricto
        while (!dq.empty() && dq.back().first <= v)
            dq.pop_back();
        dq.push_back({v,idx});
    }

    void pop(int idx_out)
    {
        // cambiar <= a < si quieres ser estricto
        if (!dq.empty() && dq.front().second <= idx_out)
            dq.pop_front();
    }

    int get() const // verificar primero empty()!!!
    {
        return dq.front().first;
    }
};

// Comparadores estándar: less<T>, less_equal<T>, greater<T>, greater_equal<T>
template<typename T, typename Compare = less<T>>
struct mono_deque
{
    deque<T> dq;
    Compare comp;

    void push_back_mono(const T& val)
    {
        while (!dq.empty() && comp(dq.back(), val))
            dq.pop_back();
        dq.push_back(val);
    }

    void push_front_mono(const T& val)
    {
        while (!dq.empty() && comp(val, dq.front()))
            dq.pop_front();
        dq.push_front(val);
    }

    void pop_back() {dq.pop_back();} // verificar empty()!!!
    void pop_front() {dq.pop_front();} // verificar empty()!!!
    const T& front() const {return dq.front();} // verificar empty()!!!
    const T& back() const {return dq.back();} // verificar empty()!!!
    bool empty() const {return dq.empty();}
    size_t size() const {return dq.size();}
};
