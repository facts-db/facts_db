# Facts

<a id="s_facts"></a>
`typedef struct facts s_facts`

Facts database. Contains an unlimited number of facts.
Each fact is a triple consisting of subject, predicate, object.
See [s_fact](#s_fact).

The database must be initialized with
[facts_init](#facts_init)
or
[new_facts](#new_facts)
before usage.

Multiple facts can be added using [facts_add](#facts_add).

A single fact can be added using [facts_add_fact](#facts_add_fact) and
[facts_add_spo](#facts_add_spo).

Multiple facts can be removed using [facts_remove](#facts_remove).

A single fact can be removed using
[facts_remove_fact](#facts_remove_fact) and
[facts_remove_spo](#facts_remove_spo).

The database can be queried using [facts_with](#facts_with) to
match and bind symbols to variables according to a pattern
(pattern matching).

---

<a id="facts_init"></a>
`void facts_init (s_facts *facts, s_set *symbols, unsigned long max)`

Initialize a *facts* database.

*Symbols* should be NULL for auto-allocation or a set consisting only
of NUL terminated strings.

The database supports an unlimited amount of symbols and facts
but performs better when the number of symbols and facts remains
below *max*. That is the max for symbols and the max for facts,
they get the same value. The maximum is only used for symbols if
symbols is NULL and thus auto-allocated.

After usage the database should be destroyed using
[facts_destroy](#facts_destroy).

---

<a id="facts_destroy"></a>
`void facts_destroy (s_facts *facts)`

Destroys a *facts* database.

Frees the associated symbols which must not be in use if the symbols
set was auto-allocated.

Frees the database facts which must not be in use.

---

<a id="new_facts"></a>
`s_facts * new_facts (s_set *symbols, unsigned long max)`

Allocate and initialize a *facts* database.

*Symbols* should be NULL for auto-allocation or a set consisting only
of NUL terminated strings.

The database supports an unlimited amount of symbols and facts
but performs better when the number of symbols and facts remains
below *max*. That is the max for symbols and the max for facts,
they get the same value. The maximum is only used for symbols if
symbols is NULL and thus auto-allocated.

After usage the database should be deleted using
[delete_facts](#delete_facts).

---

<a id="delete_facts"></a>
`void delete_facts (s_facts *facts)`

Destroy and free a *facts* database created with
[new_facts](#new_facts).

Frees the associated symbols which must not be in use if the symbols
set was auto-allocated.

Frees the database facts which must not be in use.

---

<a id="facts_find_symbol"></a>
`const char * facts_find_symbol (s_facts *facts, const char *string)`

Return an existing symbol from the symbol set associated with **facts**,
or NULL if not found.

---

<a id="facts_anon"></a>
`const char * facts_anon (s_facts *facts, const char *name)`

Return a newly interned anonymous symbol prefixed by **name**-
for use as an identifier in **facts**.

---

<a id="facts_intern"></a>
`const char * facts_intern (s_facts *facts, const char *string)`

Intern a symbol named **string**
into the set of symbols associated with **facts**.

All facts added to the database are interned first for faster
comparison.

---

<a id="facts_add_fact"></a>
`s_fact * facts_add_fact (s_facts *facts, s_fact *f)`

Add a fact to **facts**.
The fact **f** is copied and can be stack-allocated.

---

<a id="facts_add_spo"></a>
`s_fact * facts_add_spo (s_facts *facts, const char *s, const char *p, const char *o)`

Add a fact to **facts** with given subject, predicate, object.

---

<a id="facts_add"></a>
`int facts_add (s_facts *facts, p_spec spec)`

Add facts to **facts** according to **spec**.

If a fact contains a binding (starts with a `?`) it is replaced
by an anonymous symbol prefixed with the binding name, see
[facts_anon](#facts_anon).

See [spec](spec.md).

---

<a id="facts_remove_fact"></a>
`int facts_remove_fact (s_facts *facts, s_fact *f)`

Remove a fact from **facts** matching **f** if found.

Returns zero if not found, non-zero otherwise.

---

<a id="facts_remove_spo"></a>
`int facts_remove_spo (s_facts *facts, const char *s, const char *p, const char *o)`

Remove a fact from **facts** matching **s**, **p**, **o** if found.

Returns zero if not found, non-zero otherwise.

---

<a id="facts_remove"></a>
`int facts_remove (s_facts *facts, p_spec spec)`

Remove all the facts matching **spec** from **facts**.

The facts are collected from the spec using
[facts_with](#facts_with).

See [spec](spec.md).

Example :
```
       facts_remove(facts, (const char *[]){
                        "?movie", "is a", "movie",
                                  "?p", "?o", NULL, NULL});
```

---

<a id="facts_get_fact"></a>
`s_fact * facts_get_fact (s_facts *facts, s_fact *f)`

Return a fact from **facts** matching **f** if found.

---

<a id="facts_get_spo"></a>
`s_fact * facts_get_spo (s_facts *facts, const char *s, const char *p, const char *o)`

Return a fact from **facts** matching **s**, **p**, **o** if found.

---

<a id="facts_count"></a>
`unsigned long facts_count (s_facts *facts)`

Return the number of facts (triples) in **facts**.

---

<a id="s_facts_cursor"></a>
`typedef struct facts_cursor s_facts_cursor`

A cursor to iterate on facts one by one, setting bindings values.

---

<a id="facts_cursor_next"></a>
`s_fact * facts_cursor_next (s_facts_cursor *c)`

Return the next fact from iterating on the given [s_facts_cursor](#s_facts_cursor).

---

<a id="facts_with_0"></a>
`void facts_with_0 (s_facts *facts, s_facts_cursor *c, const char **var_s, const char **var_p, const char **var_o)`

Initialize a [s_facts_cursor](#s_facts_cursor) to iterate on all
triples of **facts**.

Each call to [facts_cursor_next](#facts_cursor_next) will set
**var_s**, **var_p**, **var_o**.

---

<a id="facts_with_spo"></a>
`void facts_with_spo (s_facts *facts, s_binding *bindings, s_facts_cursor *c, const char *s, const char *p, const char *o)`

Initialize a [s_facts_cursor](#s_facts_cursor) to iterate on a given triple
(**s**, **p**, **o**).

Each member of the triple can be a binding name starting with a `?`
and defined in **bindings**. See [binding](binding.md). The bindings will be
set by [facts_cursor_next](#facts_cursor_next).

Example :
```
        const char *o = NULL;
        s_binding bindings[] = {{"?o", &o}, {NULL, NULL}};
        s_facts_cursor c;
        facts_with_spo(facts, bindings, &c, s, p, "?o");
        if (facts_cursor_next(&c))
                return o;
        return NULL;
```

---

<a id="s_facts_with_cursor"></a>
`typedef struct facts_with_cursor s_facts_with_cursor`

A cursor to iterate on facts matching nested patterns with support for
binding variables.

---

<a id="facts_with_cursor_destroy"></a>
`void facts_with_cursor_destroy (s_facts_with_cursor *c)`

Destroy a [facts_with](#facts_with) cursor.
Must be called after [facts_with](#facts_with).

---

<a id="facts_with_cursor_next"></a>
`int facts_with_cursor_next (s_facts_with_cursor *c)`

Iterate on [facts_with](#facts_with) query.

If there is no next iteration the function returns 0.

If there is a next iteration for the query the bindings are set and the
function returns a non-zero value.

---

<a id="facts_with"></a>
`void facts_with (s_facts *facts, s_binding *bindings, s_facts_with_cursor *c, p_spec spec)`

Initialize a [facts with cursor](#s_facts_with_cursor) to iterate according to
the given **spec** on **facts**. **Bindings** are set for each iteration by
[facts_with_cursor_next](#facts_with_cursor_next).
See [binding](binding.md) and [spec](spec.md).

After iteration the cursor must be destroyed using
[facts_with_cursor_destroy](#facts_with_cursor_destroy).

The query is sorted to match most specific values first thus
decreasing the number of partial matches.

Example :
```
{
        const char *movie;
        const char *actor;
        const char *name;
        s_facts_with_cursor c;
        s_binding bindings = {{"?movie", &movie},
                              {"?actor", &actor},
                              {"?name", &name},
                              {NULL, NULL}};
        facts_with(facts, bindings, &c, (const char *[]) {
                        "?movie", "is a", "movie",
                                  "actor", "?actor", NULL,
                        "?actor", "is a", "actor",
                                  "name", "?name", NULL, NULL});
        while (facts_with_cursor_next(&c)) {
                printf("movie %s actor %s name %s\n",
                       movie, actor, name);
        }
        facts_with_cursor_destroy(&c);
}
```

---

<a id="facts_get_prop"></a>
`const char * facts_get_prop (s_facts *facts, const char *s,
const char *p)`

Returns the first matching object for a given subject and predicate.

---

<a id="facts_get_prop_long"></a>
`long facts_get_prop_long (s_facts *facts, const char *s,
const char *p)`

Returns the first matching object for a given subject and predicate
as a long value.

---

<a id="facts_get_prop_double"></a>
`double facts_get_prop_double (s_facts *facts, const char *s,
const char *p)`

Returns the first matching object for a given subject and predicate
as a double value.

---

<a id="facts_set_prop"></a>
`s_fact * facts_set_prop (s_facts *facts, const char *s, const char *p,
const char *o)`

Sets a property value *o* for subject *s* and predicate *p*.
Removes all other property values for *s* and *p*.

A property can be at most a single object for a given subject and
predicate.
