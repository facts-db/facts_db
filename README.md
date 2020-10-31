# facts_db

Graph database in C99.

## Documentation

<a id="s_facts"></a>
> typedef struct facts **s_facts**
>
> Facts database. Each fact is a triple consisting of
> subject, predicate, object. See [s_fact](#s_fact).

---

<a id="facts_init"></a>
> **facts_init** (s_facts *facts, s_set *symbols, unsigned long max)
>
> Initialize a facts database.
>
> Symbols should be NULL for auto-allocation or a set consisting only
> of NUL terminated strings.
>
> The database supports an unlimited amount of symbols and facts
> but performs better when the number of symbols and facts remains
> below max. That is the max for symbols and the max for facts,
> they get the same value. The maximum is only used for symbols if
> symbols is NULL and thus auto-allocated.

---

<a id="s_fact"></a>
> typedef struct fact {
>     const char *s;
>     const char *p;
>     const char *o;
> } **s_fact**
>
> A single fact. A fact consists of a subject, a predicate and an
> object.

---
