-- Find the film_title of all films which feature both KIRSTEN PALTROW and WARREN NOLTE
-- Order the results by film_title in descending order.
--  Warning: this is a tricky one and while the syntax is all things you know, you have to think a bit oustide the box to figure out how to get a table that shows pairs of actors in movies.


-- Put your query for q5 here.

SELECT title AS film_title
FROM film
WHERE film_id IN (
    SELECT film_id
    FROM film_actor
    WHERE actor_id = (
        SELECT a.actor_id
        FROM actor a
        WHERE a.first_name="KIRSTEN" AND a.last_name="PALTROW"
    )
) AND film_id IN (
    SELECT film_id
    FROM film_actor
    WHERE actor_id = (
        SELECT a.actor_id
        FROM actor a
        WHERE a.first_name="WARREN" AND a.last_name="NOLTE"
    )
)
ORDER BY title DESC;
