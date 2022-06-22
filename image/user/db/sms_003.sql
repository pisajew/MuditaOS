-- Copyright (c) 2017-2022, Mudita Sp. z.o.o. All rights reserved.
-- For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md
BEGIN TRANSACTION;
INSERT OR REPLACE INTO "templates" ("_id","text","lastUsageTimestamp",rowOrder) VALUES (1,'Thanks for reaching out. I can''t talk right now, I''ll call you later',4,1);
INSERT OR REPLACE INTO "templates" ("_id","text","lastUsageTimestamp",rowOrder) VALUES (2,'I''ll call you later',3,2);
INSERT OR REPLACE INTO "templates" ("_id","text","lastUsageTimestamp",rowOrder) VALUES (3,'I''ll be there in 15 minutes',2,3);
INSERT OR REPLACE INTO "templates" ("_id","text","lastUsageTimestamp",rowOrder) VALUES (4,'Give me 5 minutes',5,4);
COMMIT;
