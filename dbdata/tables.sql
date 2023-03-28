CREATE SEQUENCE IF NOT EXISTS zlplib.users_user_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE SEQUENCE IF NOT EXISTS zlplib.desks_desk_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE SEQUENCE IF NOT EXISTS zlplib.books_book_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE SEQUENCE IF NOT EXISTS zlplib.books_to_desks_book_desk_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE SEQUENCE IF NOT EXISTS zlplib.authors_author_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE SEQUENCE IF NOT EXISTS zlplib.genres_genre_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE SEQUENCE IF NOT EXISTS zlplib.images_image_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE TABLE IF NOT EXISTS zlplib.images
(
    image_id integer NOT NULL DEFAULT nextval('zlplib.images_image_id_seq'::regclass),
    image text NOT NULL,
    CONSTRAINT images_pkey PRIMARY KEY (image_id)
);

CREATE TABLE IF NOT EXISTS zlplib.users
(
    user_id integer NOT NULL DEFAULT nextval('zlplib.users_user_id_seq'::regclass),
    name character varying(50) NOT NULL,
    avatar integer,
    CONSTRAINT users_pkey PRIMARY KEY (user_id),
    CONSTRAINT users_avatar_fkey FOREIGN KEY (avatar)
        REFERENCES zlplib.images (image_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.desks
(
    desk_id integer NOT NULL DEFAULT nextval('zlplib.desks_desk_id_seq'::regclass),
    name character varying(50) NOT NULL,
    CONSTRAINT desks_pkey PRIMARY KEY (desk_id)
);

CREATE TABLE IF NOT EXISTS zlplib.users_to_desks
(
    desk_id integer NOT NULL,
    user_id integer NOT NULL,
    background character varying(20) NOT NULL DEFAULT "white",
    sort integer NOT NULL DEFAULT 0,
    CONSTRAINT users_to_desks_pkey PRIMARY KEY (desk_id, user_id),
    CONSTRAINT desk_id_fkey FOREIGN KEY (desk_id)
        REFERENCES zlplib.desks (desk_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT user_id_fkey FOREIGN KEY (user_id)
        REFERENCES zlplib.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.invites
(
    desk_id integer NOT NULL,
    user_id integer NOT NULL,
    status integer NOT NULL DEFAULT 0,
    CONSTRAINT invites_pkey PRIMARY KEY (desk_id, user_id),
    CONSTRAINT desk_id_fkey FOREIGN KEY (desk_id)
        REFERENCES zlplib.desks (desk_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT user_id_fkey FOREIGN KEY (user_id)
        REFERENCES zlplib.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.books
(
    book_id integer NOT NULL DEFAULT nextval('zlplib.books_book_id_seq'::regclass),
    name character varying(50) NOT NULL,
    book_cover integer,
    creation_date integer NOT NULL,
    description text,
    page_count integer,
    format integer,
    locator integer,
    owner integer,
    CONSTRAINT books_pkey PRIMARY KEY (book_id),
    CONSTRAINT books_book_cover_fkey FOREIGN KEY (book_cover)
        REFERENCES zlplib.images (image_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT books_locator_fkey FOREIGN KEY (locator)
        REFERENCES zlplib.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT books_owner_fkey FOREIGN KEY (owner)
        REFERENCES zlplib.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.books_to_desks
(
    book_desk_id integer NOT NULL DEFAULT nextval('zlplib.books_to_desks_book_desk_id_seq'::regclass),
    desk_id integer NOT NULL,
    book_id integer NOT NULL,
    CONSTRAINT books_to_desks_pkey PRIMARY KEY (book_desk_id),
    CONSTRAINT books_to_desks_desk_id_fkey FOREIGN KEY (desk_id)
        REFERENCES zlplib.desks (desk_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT books_to_desks_book_id_fkey FOREIGN KEY (book_id)
        REFERENCES zlplib.books (book_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.reviews
(
    book_desk_id integer NOT NULL,
    user_id integer NOT NULL,
    evaluation_mark integer NOT NULL,
    description text,
    CONSTRAINT reviews_pkey PRIMARY KEY (book_desk_id, user_id),
    CONSTRAINT reviews_book_desk_id_fkey FOREIGN KEY (book_desk_id)
        REFERENCES zlplib.books_to_desks (book_desk_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT reviews_user_id_fkey FOREIGN KEY (user_id)
        REFERENCES zlplib.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.authors
(
    author_id integer NOT NULL DEFAULT nextval('zlplib.authors_author_id_seq'::regclass),
    name character varying(50),
    CONSTRAINT authors_pkey PRIMARY KEY (author_id)
);

CREATE TABLE IF NOT EXISTS zlplib.authors_to_books
(
    author_id integer NOT NULL,
    book_id integer NOT NULL,
    CONSTRAINT authors_to_books_pkey PRIMARY KEY (author_id, book_id),
    CONSTRAINT authors_to_books_author_id_fkey FOREIGN KEY (author_id)
        REFERENCES zlplib.authors (author_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT authors_to_books_book_id_fkey FOREIGN KEY (book_id)
        REFERENCES zlplib.books (book_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.genres
(
    genre_id integer NOT NULL DEFAULT nextval('zlplib.genres_genre_id_seq'::regclass),
    name character varying(20),
    CONSTRAINT genres_pkey PRIMARY KEY (genre_id)
);

CREATE TABLE IF NOT EXISTS zlplib.genres_to_books
(
    genre_id integer NOT NULL,
    book_id integer NOT NULL,
    CONSTRAINT genres_to_books_pkey PRIMARY KEY (genre_id, book_id),
    CONSTRAINT genres_to_books_genre_id_fkey FOREIGN KEY (genre_id)
        REFERENCES zlplib.genres (genre_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT genres_to_books_book_id_fkey FOREIGN KEY (book_id)
        REFERENCES zlplib.books (book_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

CREATE TABLE IF NOT EXISTS zlplib.bookmarks
(
    user_id integer NOT NULL,
    book_id integer NOT NULL,
    status integer NOT NULL,
    CONSTRAINT bookmarks_pkey PRIMARY KEY (user_id, book_id),
    CONSTRAINT bookmarks_user_id_fkey FOREIGN KEY (user_id)
        REFERENCES zlplib.users (user_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT bookmarks_book_id_fkey FOREIGN KEY (book_id)
        REFERENCES zlplib.books (book_id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
);

ALTER SEQUENCE zlplib.users_user_id_seq OWNED BY users.user_id;
ALTER SEQUENCE zlplib.desks_desk_id_seq OWNED BY desks.desk_id;
ALTER SEQUENCE zlplib.books_book_id_seq OWNED BY books.book_id;
ALTER SEQUENCE zlplib.books_to_desks_book_desk_id_seq OWNED BY books_to_desks.book_desk_id;
ALTER SEQUENCE zlplib.authors_author_id_seq OWNED BY authors.author_id;
ALTER SEQUENCE zlplib.genres_genre_id_seq OWNED BY genres.genre_id;
ALTER SEQUENCE zlplib.images_image_id_seq OWNED BY images.image_id;