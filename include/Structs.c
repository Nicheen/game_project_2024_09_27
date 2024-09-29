// -----------------------------------------------------------------------
// Structs (typedef struct)
// -----------------------------------------------------------------------

typedef struct TimedEvent {
    bool is_valid;
	TimedEventWorldType worldtype;
    TimedEventType type;     // Which timed event are we referencing
	float interval;          // Time before the event starts
    float interval_timer;    // Timer for the interval
    float duration;
    float duration_timer;          // Duration of the event
    float progress;          // Current progress of the event
    int counter;             // Count how many loops we have done (useful)
} TimedEvent;

typedef struct Entity {
    TimedEvent* timer;
	TimedEvent* second_timer;
	struct Entity* child;
	// --- Entity Attributes ---
	enum EntityType entitytype;
	Vector2 size;
	Vector2 start_size;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 deceleration;
	Vector4 color;
	int start_health;
	int health;
	bool is_valid;
	// --- Entity Type Below ---
	// Obstacle
	enum ObstacleType obstacle_type;
	float wave_time;
	float wave_time_beginning;
	float drop_interval;
	float drop_interval_timer;
	float drop_duration_time;
	Vector2 grid_position;
	// Projectile
	int n_bounces;
	int max_bounces;
} Entity;

typedef struct Effect{
	bool is_valid;
	TimedEvent* timer;
	float effect_duration;
	enum EffectType effect_type;
	enum EffectSpawn effect_spawn;
} Effect;

typedef struct Player{
	Entity* entity;
	float max_speed;
	float min_speed;
	float max_bounce;
	float damp_bounce;
	float immunity_timer;
    bool is_immune;
} Player;

typedef struct ObstacleTuple {
	Entity* obstacle;
	int x;
	int y;
} ObstacleTuple;

typedef struct World {
	Entity entities[MAX_ENTITY_COUNT];
	ObstacleTuple obstacle_list[MAX_ENTITY_COUNT];
    TimedEvent timedevents[MAX_ENTITY_COUNT];
	Effect effects[MAX_EFFECT_COUNT];

	Vector4 world_background;
} World;