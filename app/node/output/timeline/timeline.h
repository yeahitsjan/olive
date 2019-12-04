/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef TIMELINEOUTPUT_H
#define TIMELINEOUTPUT_H

#include "common/timelinecommon.h"
#include "node/block/block.h"
#include "node/output/track/track.h"
#include "timeline/trackreference.h"
#include "timeline/tracktypes.h"
#include "tracklist.h"

/**
 * @brief Node that represents the end of the Timeline as well as a time traversal Node
 */
class TimelineOutput : public Node
{
  Q_OBJECT
public:
  TimelineOutput();

  virtual Node* copy() const override;

  virtual QString Name() const override;
  virtual QString id() const override;
  virtual QString Category() const override;
  virtual QString Description() const override;

  const rational& length() const;

  const QVector<TrackOutput *> &Tracks() const;

  NodeInput* track_input(TrackType type) const;

  TrackList* track_list(TrackType type) const;

  NodeOutput* length_output() const;

  const rational& timeline_length() const;

  const rational& timebase() const;

  void SetTimebase(const rational &timebase);

signals:
  void LengthChanged(const rational& length);
  void TimebaseChanged(const rational &timebase);

  void BlockAdded(Block* block, TrackReference track);
  void BlockRemoved(Block* block);

  void TrackAdded(TrackOutput* track, TrackType type);
  void TrackRemoved(TrackOutput* track);

protected:
  virtual NodeValueTable Value(const NodeValueDatabase& value) const override;

private:
  QVector<NodeInput*> track_inputs_;

  QVector<TrackList*> track_lists_;

  QVector<TrackOutput*> track_cache_;

  NodeOutput* length_output_;

  rational length_;

  rational timebase_;

private slots:
  void UpdateTrackCache();

  void UpdateLength(const rational &length);

  void TrackListAddedBlock(Block* block, int index);

  void TrackListAddedTrack(TrackOutput* track);

};

#endif // TIMELINEOUTPUT_H
