-- Find the first_name and last_name of all actors who have never been in a Sci-Fi film.
-- Order by the actor_id in ascending order.

-- Put your query for q4 here

SELECT foo.actor_id, foo.first_name, foo.last_name
FROM (
    SELECT actor.actor_id, actor.first_name, actor.last_name, IFNULL(total_combined_film_length, 0) AS total_combined_film_length
    FROM (
        SELECT first_name, last_name, SUM(film.length) AS total_combined_film_length, actor_id
        FROM (
            SELECT first_name, last_name, a.actor_id, a.film_id
            FROM (
                SELECT first_name, last_name, actor.actor_id, film_id
                FROM film_actor
                JOIN actor ON actor.actor_id = film_actor.actor_id
            ) AS a, film_category AS b
            WHERE a.film_id=b.film_id AND b.category_id=14
        ) as scifi_movies
        JOIN film on film.film_id=scifi_movies.film_id
        GROUP BY scifi_movies.actor_id
        ORDER BY scifi_movies.actor_id DESC
    ) as scifi_movies_table
    RIGHT JOIN actor on actor.actor_id=scifi_movies_table.actor_id
    GROUP BY actor.actor_id
    ORDER BY actor.actor_id ASC
) as foo
WHERE foo.total_combined_film_length=0;