# facts_db

Graph database in C99.

## Documentation

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
