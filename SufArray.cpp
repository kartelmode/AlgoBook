namespace SufArray {
    vector <int> p, c;

    void init(vector <int> &s, int &n) {
        p.resize(n); c.resize(n);
        int alph = *max_element(s.begin(), s.end()) + 1;
        vector <int> cnt(alph, 0);
        for (int i = 0; i < n; i++) {
            cnt[s[i]]++;
        }
        for (int i = 1; i < alph; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = 0; i < n; i++) {
            p[--cnt[s[i]]] = i;
        }
        c[p[0]] = 0;
        int classes = 0;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]]) {
                classes++;
            }
            c[p[i]] = classes;
        }
    }

    vector <int> build(vector <int> &s, int n) {
        init(s, n);

        vector <int> pn(n), cn(n), cnt(n);
        for (int h = 0; (1 << h) < n; h++) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) {
                    pn[i] += n;
                }
            }
            for (int i = 0; i < n; i++) {
                cnt[i] = 0;
            }
            for (int i = 0; i < n; i++) {
                cnt[c[pn[i]]]++;
            }
            for (int i = 1; i < n; i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                p[--cnt[c[pn[i]]]] = pn[i];
            }
            cn[p[0]] = 0;
            int classes = 0;
            for (int i = 1; i < n; i++) {
                int m1 = (p[i] + (1 << h)) % n, m2 = (p[i - 1] + (1 << h)) % n;
                if (c[p[i]] != c[p[i - 1]] || c[m1] != c[m2]) {
                    classes++;
                }
                cn[p[i]] = classes;
            }
            c = cn;
        }
        return p;
    }
    vector <int> build_lcp(vector <int> &s, vector <int> &p) {
        int n = (int)s.size();
        vector <int> rs(n), lcp(n);
        for (int i = 0; i < n; i++) {
            rs[p[i]] = i;
        }
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int j = rs[i];
            if (j + 1 < n) {
                while (s[p[j] + cur] == s[p[j + 1] + cur]) {
                    cur++;
                }
                lcp[j] = cur;
            }
            if (cur > 0) {
                cur--;
            }
        }
        return lcp;
    }
};