# Spec

<a id="p_spec"></a>
`typedef const char **p_spec`

Facts specification.

A spec has the following pattern :
> (subject (predicate object)+ NULL)+ NULL

For instance one fact {s1, p1.1, o1.1} has the spec :
> s1 p1.1 o1.1 NULL NULL

And four facts of two subjects, each having two properties yield this
spec :
> s1 p1.1 o1.1 p1.2 o1.2 NULL s2 p2.1 o2.1 p2.2 o2.2 NULL NULL

---

<a id="spec_clone"></a>
`p_spec spec_clone (p_spec spec)`
Clone the given spec with malloc. Must be freed after use.

---

<a id="spec_count_bindings"></a>
`size_t spec_count_bindings (p_spec spec)`
Count the bindings (strings starting with `?`) in the given spec.

---

<a id="spec_count_facts"></a>
`size_t spec_count_facts (p_spec spec)`
Count the facts (triples) in the given spec.

---

<a id="spec_expand"></a>
`p_spec spec_expand (p_spec spec)`
calls malloc to return a new p_spec of the form :
> (S P O NULL)* NULL

---

<a id="spec_print"></a>
`void spec_print (p_spec spec, FILE *fp)`
Print the spec to open file descriptor fp. The file descriptor must
be open for writing.

---

<a id="spec_sort"></a>
`p_spec spec_sort (p_spec spec)`
Sort an expanded spec in place. The given spec must be of the form :
> (S P O NULL)* NULL

---

<a id="s_spec_cursor"></a>
`typedef struct spec_cursor s_spec_cursor`
A spec cursor for iterating on facts (triples) of a spec.

The cursor must be initialized using
[spec_cursor_init](#spec_cursor_init).

---

<a id="spec_cursor_init"></a>
`void spec_cursor_init (s_spec_cursor *c, p_spec spec)`

Initialize a spec cursor to iterate on facts of the given spec.

---

<a id="spec_cursor_next"></a>
`int  spec_cursor_next (s_spec_cursor *c, s_fact *f)`

Iterate on spec with given cursor which must be initialized using
[spec_cursor_init](#spec_cursor_init).
The current fact is copied into the given fact pointer which can be on stack.

Example :
```
        s_spec_cursor c;
        s_fact f;
        spec_cursor_init(&c, (const char *[]){
                "a", "b", "c", "d", "e", NULL, NULL});
        if (spec_cursor_next(&c, &f))
                ; /* f contains {"a", "b", "c"} */
        if (spec_cursor_next(&c, &f))
                ; /* f contains {"a", "d", "e"} */
        if (spec_cursor_next(&c, &f))
                ; /* returns false */
```
