select title from movies
join stars on stars.movie_id = movies.id
join people on stars.person_id = people.id
where name = 'Helena Bonham Carter'
intersect
select title from movies
join stars on stars.movie_id = movies.id
join people on stars.person_id = people.id
where name = 'Johnny Depp'