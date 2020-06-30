const int K = 26;

struct Vertex{
    int next[K];
    bool leaf = false;
    int p = -1;
    char pch;
    int link = -1;
    int go[K];

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> st(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (st[v].next[c] == -1) {
            st[v].next[c] = st.size();
            st.emplace_back(v, ch);
        }
        v = st[v].next[c];
    }
    st[v].leaf = true;
}

int go(int v, char ch);

int get_link(int v) {
    if (st[v].link == -1) {
        if (v == 0 || st[v].p == 0)
            st[v].link = 0;
        else
            st[v].link = go(get_link(st[v].p), st[v].pch);
    }
    return st[v].link;
}

int go(int v, char ch) {
    int c = ch - 'a';
    if (st[v].go[c] == -1) {
        if (st[v].next[c] != -1)
            st[v].go[c] = st[v].next[c];
        else
            st[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return st[v].go[c];
}