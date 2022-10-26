-- We want to find out how many of each category of film ED CHASE has starred in.

-- So return a table with category_name and the count of the number_of_films that ED was in that category.

-- Your query should return every category even if ED has been in no films in that category

-- Order by the category name in ascending order.

SELECT name AS category_name, IFNULL(number_of_films, 0) AS number_of_films
FROM (
	SELECT category_id, COUNT(*) as number_of_films
	FROM film_category
	WHERE film_id IN (
    	SELECT film_id
    	FROM film_actor
    	WHERE actor_id IN (
        	SELECT actor_id
        	FROM actor
        	WHERE first_name="ED" AND last_name="CHASE"
    	)
	)
	GROUP BY category_id
) as num_films
RIGHT JOIN category ON category.category_id = num_films.category_id;
