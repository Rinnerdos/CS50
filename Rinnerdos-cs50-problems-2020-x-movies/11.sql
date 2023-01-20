select title from movies
join ratings
on movies.id = ratings.movie_id
join stars
on movies.id = stars.movie_id
join people
on people.id = stars.person_id
where name = 'Chadwick Boseman'
order by ratings.rating DESC
limit 5