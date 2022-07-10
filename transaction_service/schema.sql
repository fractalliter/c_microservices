CREATE TABLE IF NOT EXISTS Account(  
        user_id serial PRIMARY KEY,
        username VARCHAR (50) NOT NULL,
        balance integer NOT NULL
);

INSERT INTO Account VALUES(1,'johndoe',52642);
INSERT INTO Account VALUES(2,'janedoe',45672);
INSERT INTO Account VALUES(3,'leotolo',34322);
INSERT INTO Account VALUES(4,'stephanfera',323);
INSERT INTO Account VALUES(5,'markzuc',3325);
INSERT INTO Account VALUES(6,'ahmadbala',6544);