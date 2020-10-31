# Fact

<a id="s_fact"></a>
```
typedef struct fact {
    const char *s;
    const char *p;
    const char *o;
} s_fact
```

A single fact. A fact consists of a subject, a predicate and an
object.

---

<a id="fact_init"></a>
`void fact_init (s_fact *f, const char *s, const char *p, const char *o)`

Initialize a fact with given subject, predicate, object.

---

<a id="new_fact"></a>
`s_fact * new_fact (const char *s, const char *p, const char *o)`

Allocate and initialize a fact with given subject, predicate, object.
The returned fact must be freed with free(3) or
[delete_fact](#delete_fact).

---

<a id="delete_fact"></a>
`void delete_fact (s_fact *f)`

Free the given fact. The fact must be allocated using malloc(3) or
[new_fact](#new_fact).

---

<a id="fact_compare_spo"></a>
`int fact_compare_spo (void *a, void *b)`

Compare two facts with subject, predicate, object order.

---

<a id="fact_compare_pos"></a>
`int fact_compare_pos (void *a, void *b)`

Compare two facts with predicate, object, subject order.

---

<a id="fact_compare_osp"></a>
`int fact_compare_osp (void *a, void *b)`

Compare two facts with object, subject, predicate order.
