--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = true;

--
-- Name: banner; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE banner (
    banner_id integer NOT NULL,
    link_address character varying,
    image_url character varying,
    title character varying
);


ALTER TABLE public.banner OWNER TO vagrant;

--
-- Name: city; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE city (
    city_id integer NOT NULL,
    city_name character varying
);


ALTER TABLE public.city OWNER TO vagrant;

--
-- Name: event; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE event (
    event_id integer NOT NULL,
    event_date timestamp without time zone,
    tournament_id integer,
    place_id integer
);


ALTER TABLE public.event OWNER TO vagrant;

--
-- Name: place; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE place (
    place_id integer NOT NULL,
    place_name character varying,
    city_id integer
);


ALTER TABLE public.place OWNER TO vagrant;

--
-- Name: player; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE player (
    player_id integer NOT NULL,
    player_name character varying,
    player_surname character varying,
    player_type character varying,
    team_id integer
);


ALTER TABLE public.player OWNER TO vagrant;

--
-- Name: team; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE team (
    team_id integer NOT NULL,
    team_name character varying,
    team_player_count integer,
    event_id integer
);


ALTER TABLE public.team OWNER TO vagrant;

SET default_with_oids = false;

--
-- Name: toplist; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE toplist (
    toplist_id integer NOT NULL,
    toplist_name character varying,
    event_id integer,
    player_id integer
);


ALTER TABLE public.toplist OWNER TO vagrant;

SET default_with_oids = true;

--
-- Name: tournament; Type: TABLE; Schema: public; Owner: vagrant; Tablespace: 
--

CREATE TABLE tournament (
    tournament_id integer NOT NULL,
    tournament_name character varying,
    tournament_type character varying,
    tournament_date date,
    tournament_length integer
);


ALTER TABLE public.tournament OWNER TO vagrant;

--
-- Data for Name: banner; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY banner (banner_id, link_address, image_url, title) FROM stdin;
1	asdsa	qewqas	asdsaqw
\.


--
-- Data for Name: city; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY city (city_id, city_name) FROM stdin;
\.


--
-- Data for Name: event; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY event (event_id, event_date, tournament_id, place_id) FROM stdin;
\.


--
-- Data for Name: place; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY place (place_id, place_name, city_id) FROM stdin;
\.


--
-- Data for Name: player; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY player (player_id, player_name, player_surname, player_type, team_id) FROM stdin;
\.


--
-- Data for Name: team; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY team (team_id, team_name, team_player_count, event_id) FROM stdin;
\.


--
-- Data for Name: toplist; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY toplist (toplist_id, toplist_name, event_id, player_id) FROM stdin;
\.


--
-- Data for Name: tournament; Type: TABLE DATA; Schema: public; Owner: vagrant
--

COPY tournament (tournament_id, tournament_name, tournament_type, tournament_date, tournament_length) FROM stdin;
1	tour de france	type1	2015-12-25	50
\.


--
-- Name: banner_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY banner
    ADD CONSTRAINT banner_pkey PRIMARY KEY (banner_id);


--
-- Name: city_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY city
    ADD CONSTRAINT city_pkey PRIMARY KEY (city_id);


--
-- Name: event_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY event
    ADD CONSTRAINT event_pkey PRIMARY KEY (event_id);


--
-- Name: place_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY place
    ADD CONSTRAINT place_pkey PRIMARY KEY (place_id);


--
-- Name: player_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY player
    ADD CONSTRAINT player_pkey PRIMARY KEY (player_id);


--
-- Name: team_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY team
    ADD CONSTRAINT team_pkey PRIMARY KEY (team_id);


--
-- Name: toplist_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY toplist
    ADD CONSTRAINT toplist_pkey PRIMARY KEY (toplist_id);


--
-- Name: tournament_pkey; Type: CONSTRAINT; Schema: public; Owner: vagrant; Tablespace: 
--

ALTER TABLE ONLY tournament
    ADD CONSTRAINT tournament_pkey PRIMARY KEY (tournament_id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

