#include <include/api.h>

void Prefab_new_w_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Prefab);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    ecs_add(world, e_1, Velocity);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Velocity));
    test_assert( ecs_has(world, e_1, Prefab));
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    ecs_entity_t e_2 = ecs_new(world, Prefab);
    test_assert( ecs_has(world, e_2, Position));
    test_assert( ecs_has(world, e_2, Prefab));
    test_assert( !ecs_has(world, e_2, EcsPrefab));
    test_assert( !ecs_has(world, e_2, EcsId));
    test_assert( !ecs_get_ptr(world, e_2, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_2, EcsId));

    ecs_add(world, e_2, Velocity);
    test_assert( ecs_has(world, e_2, Position));
    test_assert( ecs_has(world, e_2, Velocity));
    test_assert( ecs_has(world, e_2, Prefab));
    test_assert( !ecs_has(world, e_2, EcsPrefab));
    test_assert( !ecs_has(world, e_2, EcsId));
    test_assert( !ecs_get_ptr(world, e_2, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_2, EcsId));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);

    test_assert(p_1 != NULL);
    test_assert(p_2 != NULL);
    test_assert(p_prefab != NULL);
    test_assert(p_1 == p_2);
    test_assert(p_1 == p_prefab);

    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Velocity *v_1 = ecs_get_ptr(world, e_1, Velocity);
    Velocity *v_2 = ecs_get_ptr(world, e_2, Velocity);
    
    test_assert(v_1 != NULL);
    test_assert(v_2 != NULL);
    test_assert(v_1 != v_2);

    ecs_fini(world);
}

void Prefab_new_w_count_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_start = ecs_new_w_count(world, Prefab, 10);

    int i;
    Position *p_prev = NULL;
    for (i = e_start; i < (e_start + 10); i ++) {
        Position *p = ecs_get_ptr(world, i, Position);
        test_assert(p != NULL);

        if (p_prev) test_ptr(p, p_prev);
        test_int(p->x, 10);
        test_int(p->y, 20);

        p_prev = p;
    }

    ecs_fini(world);
}

void Prefab_new_w_type_w_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position);
    ECS_TYPE(world, Type, Prefab, Velocity);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));

    ecs_entity_t e_2 = ecs_new(world, Type);
    test_assert( ecs_has(world, e_2, Position));
    test_assert( ecs_has(world, e_2, Prefab));
    test_assert( !ecs_has(world, e_2, EcsPrefab));
    test_assert( !ecs_has(world, e_2, EcsId));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);

    test_assert(p_1 != NULL);
    test_assert(p_2 != NULL);
    test_assert(p_1 == p_2);
    test_assert(p_1 == p_prefab);

    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Velocity *v_1 = ecs_get_ptr(world, e_1, Velocity);
    Velocity *v_2 = ecs_get_ptr(world, e_2, Velocity);
    
    test_assert(v_1 != NULL);
    test_assert(v_2 != NULL);
    test_assert(v_1 != v_2);

    ecs_fini(world);
}

void Prefab_add_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Velocity);
    test_assert(e_1 != 0);

    ecs_add(world, e_1, Prefab);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));

    ecs_entity_t e_2 = ecs_new(world, Velocity);
    test_assert(e_2 != 0);

    ecs_add(world, e_2, Prefab);
    test_assert( ecs_has(world, e_2, Position));
    test_assert( ecs_has(world, e_2, Prefab));
    test_assert( !ecs_has(world, e_2, EcsPrefab));
    test_assert( !ecs_has(world, e_2, EcsId));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);

    test_assert(p_1 != NULL);
    test_assert(p_2 != NULL);
    test_assert(p_1 == p_2);
    test_assert(p_prefab == p_1);

    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Velocity *v_1 = ecs_get_ptr(world, e_1, Velocity);
    Velocity *v_2 = ecs_get_ptr(world, e_2, Velocity);
    
    test_assert(v_1 != NULL);
    test_assert(v_2 != NULL);
    test_assert(v_1 != v_2);

    ecs_fini(world);
}

void Prefab_add_type_w_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position);
    ECS_TYPE(world, Type, Prefab, Velocity);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_add(world, e_1, Type);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));

    ecs_entity_t e_2 = ecs_new(world, 0);

    ecs_add(world, e_2, Type);
    test_assert( ecs_has(world, e_2, Position));
    test_assert( ecs_has(world, e_2, Prefab));
    test_assert( !ecs_has(world, e_2, EcsPrefab));
    test_assert( !ecs_has(world, e_2, EcsId));

    Position *p_1 = ecs_get_ptr(world, e_1, Position);
    Position *p_2 = ecs_get_ptr(world, e_2, Position);
    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);

    test_assert(p_1 != NULL);
    test_assert(p_2 != NULL);
    test_assert(p_1 == p_2);
    test_assert(p_prefab == p_1);

    test_int(p_1->x, 10);
    test_int(p_1->y, 20);

    Velocity *v_1 = ecs_get_ptr(world, e_1, Velocity);
    Velocity *v_2 = ecs_get_ptr(world, e_2, Velocity);
    
    test_assert(v_1 != NULL);
    test_assert(v_2 != NULL);
    test_assert(v_1 != v_2);

    ecs_fini(world);
}

void Prefab_remove_prefab_after_new() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Prefab);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    ecs_remove(world, e_1, Prefab);
    test_assert( !ecs_has(world, e_1, Position));
    test_assert( !ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    ecs_fini(world);
}

void Prefab_remove_prefab_after_add() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_add(world, e_1, Prefab);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    ecs_remove(world, e_1, Prefab);
    test_assert( !ecs_has(world, e_1, Position));
    test_assert( !ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    ecs_fini(world);
}

void Prefab_override_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Prefab);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_set(world, e_1, Position, {20, 30});
    p = ecs_get_ptr(world, e_1, Position);
    test_int(p->x, 20);
    test_int(p->y, 30);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    ecs_fini(world);
}

void Prefab_override_remove_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Prefab);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_set(world, e_1, Position, {20, 30});
    p = ecs_get_ptr(world, e_1, Position);
    test_int(p->x, 20);
    test_int(p->y, 30);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p_prefab != NULL);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    ecs_remove(world, e_1, Position);
    p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_assert(p == p_prefab);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Prefab_override_2_of_3_components_1_self() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Rotation);
    ECS_PREFAB(world, Prefab, Position, Velocity, Mass);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});
    ecs_set(world, Prefab, Mass, {50});

    ecs_entity_t e_1 = ecs_new(world, Prefab);
    test_assert(e_1 != 0);

    ecs_set(world, e_1, Rotation, {60});

    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Velocity));
    test_assert( ecs_has(world, e_1, Mass));
    test_assert( ecs_has(world, e_1, Rotation));
    test_assert( ecs_has(world, e_1, Prefab));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_set(world, e_1, Position, {20, 30});
    p = ecs_get_ptr(world, e_1, Position);
    test_int(p->x, 20);
    test_int(p->y, 30);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    ecs_set(world, e_1, Velocity, {40, 50});
    v = ecs_get_ptr(world, e_1, Velocity);
    test_int(v->x, 40);
    test_int(v->y, 50);

    Velocity *v_prefab = ecs_get_ptr(world, Prefab, Velocity);
    test_assert(v != v_prefab);
    test_int(v_prefab->x, 30);
    test_int(v_prefab->y, 40);

    Mass *m = ecs_get_ptr(world, e_1, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    Mass *m_prefab = ecs_get_ptr(world, Prefab, Mass);
    test_assert(m_prefab != NULL);
    test_ptr(m_prefab, m);

    Rotation *r = ecs_get_ptr(world, e_1, Rotation);
    test_assert(r != NULL);
    test_int(*r, 60);

    ecs_fini(world);
}

void Prefab_new_type_w_1_override() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position, Velocity);
    ECS_TYPE(world, Type, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Velocity));
    test_assert( ecs_has(world, e_1, Prefab));
    test_assert( ecs_has(world, e_1, Type));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p_prefab != NULL);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    Velocity *v_prefab = ecs_get_ptr(world, Prefab, Velocity);
    test_assert(v_prefab != NULL);
    test_assert(v == v_prefab);
    test_int(v_prefab->x, 30);
    test_int(v_prefab->y, 40);

    ecs_fini(world);
}

void Prefab_new_type_w_2_overrides() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position, Velocity);
    ECS_TYPE(world, Type, Prefab, Position, Velocity);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Velocity));
    test_assert( ecs_has(world, e_1, Prefab));
    test_assert( ecs_has(world, e_1, Type));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p_prefab != NULL);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    Velocity *v_prefab = ecs_get_ptr(world, Prefab, Velocity);
    test_assert(v_prefab != NULL);
    test_assert(v != v_prefab);
    test_int(v_prefab->x, 30);
    test_int(v_prefab->y, 40);

    ecs_fini(world);
}

void Prefab_add_type_w_1_overrides() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position, Velocity);
    ECS_TYPE(world, Type, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});

    ecs_entity_t e_1 = ecs_new(world, 0);
    test_assert(e_1 != 0);

    ecs_add(world, e_1, Type);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Velocity));
    test_assert( ecs_has(world, e_1, Prefab));
    test_assert( ecs_has(world, e_1, Type));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p_prefab != NULL);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    Velocity *v_prefab = ecs_get_ptr(world, Prefab, Velocity);
    test_assert(v_prefab != NULL);
    test_assert(v == v_prefab);
    test_int(v_prefab->x, 30);
    test_int(v_prefab->y, 40);

    ecs_fini(world);
}

void Prefab_add_type_w_2_overrides() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position, Velocity);
    ECS_TYPE(world, Type, Prefab, Position, Velocity);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);

    ecs_add(world, e_1, Type);
    test_assert( ecs_has(world, e_1, Position));
    test_assert( ecs_has(world, e_1, Velocity));
    test_assert( ecs_has(world, e_1, Prefab));
    test_assert( ecs_has(world, e_1, Type));
    /* These components should never be inherited from prefabs */
    test_assert( !ecs_has(world, e_1, EcsPrefab));
    test_assert( !ecs_has(world, e_1, EcsId));
    test_assert( !ecs_get_ptr(world, e_1, EcsPrefab));
    test_assert( !ecs_get_ptr(world, e_1, EcsId));

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    Position *p_prefab = ecs_get_ptr(world, Prefab, Position);
    test_assert(p_prefab != NULL);
    test_assert(p != p_prefab);
    test_int(p_prefab->x, 10);
    test_int(p_prefab->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    Velocity *v_prefab = ecs_get_ptr(world, Prefab, Velocity);
    test_assert(v_prefab != NULL);
    test_assert(v != v_prefab);
    test_int(v_prefab->x, 30);
    test_int(v_prefab->y, 40);

    ecs_fini(world);
}

void Prefab_get_ptr_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);

    ecs_set(world, Prefab, Position, {10, 20});

    ecs_entity_t e_1 = ecs_new(world, Prefab);
    test_assert(e_1 != 0);
    test_assert( ecs_has(world, e_1, Prefab));
    test_assert( ecs_get_ptr(world, e_1, Prefab) == NULL);

    ecs_fini(world);
}

static
void Prefab_w_field(ecs_rows_t *rows) {
    ProbeSystem(rows);

    for (int i = 0; i < rows->count; i ++) {
        Position *p = ecs_field(rows, Position, i, 1);
        Velocity *v = ecs_field(rows, Velocity, i, 2);
        p->x += v->x;
        p->y += v->y;
    }
}

void Prefab_iterate_w_prefab_field() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Velocity);
    ECS_TYPE(world, Type, Prefab, Position);
    ECS_SYSTEM(world, Prefab_w_field, EcsOnUpdate, Position, Velocity);

    ecs_set(world, Prefab, Velocity, {1, 2});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);
    ecs_set(world, e_1, Position, {0, 0});

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Prefab_w_field);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.c[0][0], ecs_to_entity(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_to_entity(Velocity));
    test_int(ctx.s[0][1], Prefab);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);    

    ecs_fini(world);
}

static
void Prefab_w_shared(ecs_rows_t *rows) {
    Velocity *v = ecs_shared(rows, Velocity, 2);
    Mass *m = ecs_shared_test(rows, Mass, 3);

    test_assert(v != NULL);

    ProbeSystem(rows);

    for (int i = 0; i < rows->count; i ++) {
        Position *p = ecs_field(rows, Position, i, 1);
        p->x += v->x;
        p->y += v->y;

        if (m) {
            p->x += *m;
            p->y += *m;
        }
    }
}

void Prefab_iterate_w_prefab_shared() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Velocity);
    ECS_TYPE(world, Type, Prefab, Position);
    ECS_SYSTEM(world, Prefab_w_shared, EcsOnUpdate, Position, Velocity);

    ecs_set(world, Prefab, Velocity, {1, 2});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);
    ecs_set(world, e_1, Position, {0, 0});

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Prefab_w_shared);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.c[0][0], ecs_to_entity(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_to_entity(Velocity));
    test_int(ctx.s[0][1], Prefab);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    ecs_fini(world);
}

void Prefab_match_entity_prefab_w_system_optional() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_PREFAB(world, Prefab, Velocity, Mass);
    ECS_TYPE(world, Type, Prefab, Position);
    ECS_SYSTEM(world, Prefab_w_shared, EcsOnUpdate, Position, Velocity, ?Mass);

    ecs_set(world, Prefab, Velocity, {1, 2});
    ecs_set(world, Prefab, Mass, {3});

    ecs_entity_t e_1 = ecs_new(world, Type);
    test_assert(e_1 != 0);
    ecs_set(world, e_1, Position, {0, 0});

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Prefab_w_shared);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.c[0][0], ecs_to_entity(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_to_entity(Velocity));
    test_int(ctx.s[0][1], Prefab);
    test_int(ctx.c[0][2], ecs_to_entity(Mass));
    test_int(ctx.s[0][2], Prefab);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 4);
    test_int(p->y, 5);

    ecs_fini(world);
}

void Prefab_prefab_in_system_expr() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_PREFAB(world, Prefab1, Velocity);
    ECS_PREFAB(world, Prefab2, Velocity);
    ECS_SYSTEM(world, Prefab_w_shared, EcsOnUpdate, Position, Velocity, Prefab1);

    ecs_set(world, Prefab1, Velocity, {1, 2});
    ecs_set(world, Prefab2, Velocity, {1, 2});

    ecs_entity_t e_1 = ecs_new(world, Prefab1);
    ecs_entity_t e_2 = ecs_new(world, Prefab1);
    ecs_entity_t e_3 = ecs_new(world, Prefab2);

    test_assert(e_1 != 0);
    test_assert(e_2 != 0);
    test_assert(e_3 != 0);

    ecs_set(world, e_1, Position, {0, 0});
    ecs_set(world, e_2, Position, {0, 0});
    ecs_set(world, e_3, Position, {0, 0});

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, Prefab_w_shared);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.c[0][0], ecs_to_entity(Position));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[0][1], ecs_to_entity(Velocity));
    test_int(ctx.s[0][1], Prefab1);
    test_int(ctx.c[0][2], Prefab1);
    test_int(ctx.s[0][2], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 1);
    test_int(p->y, 2);

    ecs_fini(world);
}

void Dummy(ecs_rows_t *rows) {
    ProbeSystem(rows);
}

void Prefab_dont_match_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_PREFAB(world, Prefab, Position);
    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 0);
    test_int(ctx.invoked, 0);

    ecs_fini(world);
}

void Prefab_new_w_count_w_override() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, Prefab, Position, Velocity);
    ECS_TYPE(world, Type, Prefab, Velocity);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});

    ecs_entity_t e_1 = ecs_new_w_count(world, Type, 100);
    test_assert(e_1 != 0);

    Position *prefab_p = ecs_get_ptr(world, Prefab, Position);
    Velocity *prefab_v = ecs_get_ptr(world, Prefab, Velocity);

    ecs_entity_t e;
    for (e = e_1; e < (e_1 + 100); e ++) {
        test_assert( ecs_has(world, e, Position));
        test_assert( ecs_has(world, e, Velocity));
        test_assert( ecs_has(world, e, Prefab));

        Position *p = ecs_get_ptr(world, e, Position);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_assert(p == prefab_p);

        Velocity *v = ecs_get_ptr(world, e, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30);
        test_int(v->y, 40);
        test_assert(v != prefab_v);
    }

    ecs_fini(world);
}

void Prefab_override_2_components_different_size() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Color);
    ECS_PREFAB(world, Prefab, Position, Velocity, Color);
    ECS_TYPE(world, Type, Prefab, Velocity, Color);

    ecs_set(world, Prefab, Position, {10, 20});
    ecs_set(world, Prefab, Velocity, {30, 40});
    ecs_set(world, Prefab, Color, {1, 2, 3, 4});

    ecs_entity_t e_1 = ecs_new_w_count(world, Type, 100);
    test_assert(e_1 != 0);

    Position *prefab_p = ecs_get_ptr(world, Prefab, Position);
    Velocity *prefab_v = ecs_get_ptr(world, Prefab, Velocity);
    Color *prefab_c = ecs_get_ptr(world, Prefab, Color);

    test_assert(prefab_p != NULL);
    test_assert(prefab_v != NULL);
    test_assert(prefab_c != NULL);

    ecs_entity_t e;
    for (e = e_1; e < (e_1 + 100); e ++) {
        test_assert( ecs_has(world, e, Position));
        test_assert( ecs_has(world, e, Velocity));
        test_assert( ecs_has(world, e, Prefab));

        Position *p = ecs_get_ptr(world, e, Position);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_assert(p == prefab_p);

        Velocity *v = ecs_get_ptr(world, e, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30);
        test_int(v->y, 40);
        test_assert(v != prefab_v);

        Color *c = ecs_get_ptr(world, e, Color);
        test_assert(c != NULL);
        test_int(c->r, 1);
        test_int(c->g, 2);
        test_int(c->b, 3);
        test_int(c->a, 4);        
        test_assert(c != prefab_c);        
    }

    ecs_fini(world);
}
